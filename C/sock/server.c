#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define MAX_CONNECTIONS 2

typedef struct {
  int sock;
  struct sockaddr_in addr;
} Server;

typedef struct {
  int sock;
  struct sockaddr_in addr;
  char buf[BUF_SIZE];
} Client;

typedef struct {
  int conn_count;
  pthread_mutex_t mutex;
} State;

State state;

void inc_conn_count() {
  pthread_mutex_lock(&state.mutex);
  state.conn_count++;
  pthread_mutex_unlock(&state.mutex);
}

void dec_conn_count() {
  pthread_mutex_lock(&state.mutex);
  state.conn_count--;
  pthread_mutex_unlock(&state.mutex);
}

void serve(Server* server, uint16_t port) {
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

  if (listen(server->sock, MAX_CONNECTIONS) < 0) {
    perror("failed to listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening on port %d...\n", port);
}

void* process(void* arg) {
  printf("Active threads: %d\n", state.conn_count);

  Client* client = (Client*)arg;

  while (true) {
    int n = read(client->sock, client->buf, BUF_SIZE);
    if (n <= 0) {
      printf(
          "Client disconnected %s:%d\n", inet_ntoa(client->addr.sin_addr), client->addr.sin_port
      );
      break;
    }

    printf("Received: %s", client->buf);
    send(client->sock, client->buf, n, 0);
    memset(client->buf, 0, n);
  }

  close(client->sock);
  free(client);
  dec_conn_count();

  return NULL;
}

int main() {
  /* Server server;
  serve(&server, 8000);

  pthread_mutex_init(&state.mutex, NULL);
  state.conn_count = 0;

  while (true) {
    pthread_mutex_lock(&state.mutex);
    if (state.conn_count >= MAX_CONNECTIONS) {
      pthread_mutex_unlock(&state.mutex);
      usleep(100000);
      continue;
    }
    pthread_mutex_unlock(&state.mutex);

    Client* client = malloc(sizeof(Client));
    if (!client) {
      perror("failed to allocate client");
      continue;
    }

    socklen_t addrlen = sizeof(client->addr);
    client->sock = accept(server.sock, (struct sockaddr*)&client->addr, &addrlen);

    if (client->sock < 0) {
      perror("failed to accept");
      free(client);
      continue;
    }

    inc_conn_count();
    printf("Client connected %s:%d\n", inet_ntoa(client->addr.sin_addr), client->addr.sin_port);

    pthread_t thread;
    if (pthread_create(&thread, NULL, process, client) != 0) {
      perror("failed to create thread");
      close(client->sock);
      free(client);
      dec_conn_count();
      continue;
    }
    pthread_detach(thread);
  }

  close(server.sock);
  pthread_mutex_destroy(&state.mutex); */
}
