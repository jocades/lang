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

void init_state(State* state) {
  pthread_mutex_init(&state->mutex, NULL);
  state->conn_count = 0;
}

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
  Connection* conn;
  ConnectionCallback callback;
} Env;

Env* create_env(State* state, Connection* conn, ConnectionCallback callback) {
  Env* env = malloc(sizeof(Env));
  if (!env) {
    error("failed to allocate env");
    return NULL;
  }
  env->state = state;
  env->conn = conn;
  env->callback = callback;
  return env;
}

void* process(void* arg) {
  Env* env = (Env*)arg;
  env->callback(env->conn);

  close(env->conn->sock);
  free(env->conn);
  dec_conn_count(env->state);
  free(env);

  return NULL;
}

void run(Server* server, ConnectionCallback callback) {
  State state;
  init_state(&state);

  while (true) {
    pthread_mutex_lock(&state.mutex);
    if (state.conn_count >= server->max_connections) {
      pthread_mutex_unlock(&state.mutex);
      usleep(100000);
      continue;
    }
    pthread_mutex_unlock(&state.mutex);

    Connection* conn = malloc(sizeof(Connection));
    if (!conn) {
      error("failed to allocate client");
      continue;
    }

    socklen_t addrlen = sizeof(conn->peer);
    conn->sock = accept(server->sock, (struct sockaddr*)&conn->peer, &addrlen);
    if (conn->sock < 0) {
      perror("failed to accept");
      free(conn);
      continue;
    }

    inc_conn_count(&state);
    info("Client connected %d", conn->peer.sin_port);

    Env* env = create_env(&state, conn, callback);
    if (!env) continue;

    pthread_t thread;
    if (pthread_create(&thread, NULL, process, env) != 0) {
      perror("failed to create thread");
      close(conn->sock);
      free(conn);
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
