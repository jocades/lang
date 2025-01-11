#include "server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "log.h"

typedef struct {
  int conn_count;
  pthread_mutex_t mutex;
} State;

void inc_conn_count(State* state) {
  pthread_mutex_lock(&state->mutex);
  state->conn_count++;
  pthread_mutex_unlock(&state->mutex);
}

void dec_conn_count(State* state) {
  pthread_mutex_lock(&state->mutex);
  state->conn_count--;
  pthread_mutex_unlock(&state->mutex);
}

typedef struct {
  State* state;
  Client* client;
  ConnectionCallback callback;
} Env;

void* process(void* arg) {
  Env* env = (Env*)arg;
  trace("threads=%d", env->state->conn_count);

  env->callback(env->client);

  close(env->client->sock);
  free(env->client);
  dec_conn_count(env->state);
  free(env);

  return NULL;
}

void run(Server* server, ConnectionCallback callback) {
  State state;
  pthread_mutex_init(&state.mutex, NULL);
  state.conn_count = 0;

  while (true) {
    pthread_mutex_lock(&state.mutex);
    if (state.conn_count >= server->max_connections) {
      pthread_mutex_unlock(&state.mutex);
      usleep(100000);
      continue;
    }
    pthread_mutex_unlock(&state.mutex);

    Client* client = malloc(sizeof(Client));
    if (!client) {
      error("failed to allocate client");
      continue;
    }

    socklen_t addrlen = sizeof(client->addr);
    client->sock = accept(server->sock, (struct sockaddr*)&client->addr, &addrlen);
    if (client->sock < 0) {
      perror("failed to accept");
      free(client);
      continue;
    }

    inc_conn_count(&state);
    info("Client connected %d", client->addr.sin_port);

    Env* env = malloc(sizeof(Env));
    env->state = &state;
    env->client = client;
    env->callback = callback;
    pthread_t thread;
    if (pthread_create(&thread, NULL, process, env) != 0) {
      perror("failed to create thread");
      close(client->sock);
      free(client);
      dec_conn_count(&state);
      continue;
    }
    pthread_detach(thread);
  }

  close(server->sock);
  pthread_mutex_destroy(&state.mutex);
}

void serve(Server* server, uint16_t port, ConnectionCallback callback) {
  server->sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server->sock < 0) {
    perror("failed to create socket");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(server->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
    perror("failed to set socket options");
    exit(EXIT_FAILURE);
  }

  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = INADDR_ANY;
  server->addr.sin_port = htons(port);

  if (bind(server->sock, (struct sockaddr*)&server->addr, sizeof(server->addr)) < 0) {
    perror("failed to bind socket");
    exit(EXIT_FAILURE);
  }

  if (listen(server->sock, server->max_connections) < 0) {
    perror("failed to listen");
    exit(EXIT_FAILURE);
  }

  info("Listening on port %d...", port);

  run(server, callback);
}
