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

void serve(Server* server, uint16_t port) {
  server->sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server->sock < 0) {
    perror("failed to create socket");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  int err =
      setsockopt(server->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (err != 0) {
    perror("failed to set SO_REUSEADDR");
    exit(EXIT_FAILURE);
  }

  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = INADDR_ANY;
  server->addr.sin_port = htons(port);
  socklen_t addrlen = sizeof(server->addr);

  err = bind(server->sock, (struct sockaddr*)&server->addr, addrlen);
  if (err < 0) {
    perror("failed to bind socket");
    exit(EXIT_FAILURE);
  }

  err = listen(server->sock, MAX_CONNECTIONS);
  if (err < 0) {
    perror("failed to listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening @ localhost:%d\n", port);
}

void* process(void* arg) {
  Client* client = (Client*)arg;

  while (true) {
    int n = read(client->sock, client->buf, BUF_SIZE);
    if (n <= 0) {
      printf(
          "Client disconnected %s:%d\n", inet_ntoa(client->addr.sin_addr),
          client->addr.sin_port
      );
      break;
    }

    printf("Received: %s", client->buf);
    send(client->sock, client->buf, n, 0);
    memset(client->buf, 0, n);
  }

  close(client->sock);
  free(client);

  return NULL;
}

int main() {
  Server server;
  serve(&server, 8000);

  state.conn_count = 0;
  pthread_mutex_init(&state.mutex, NULL);

  while (true) {
    Client* client = malloc(sizeof(Client));
    if (client == NULL) {
      perror("failed to allocate client");
      continue;
    }

    socklen_t addrlen = sizeof(client->addr);
    client->sock =
        accept(server.sock, (struct sockaddr*)&client->addr, &addrlen);

    if (client->sock < 0) {
      perror("failed to accept");
      free(client);
      continue;
    }

    printf(
        "New client connected %s:%d\n", inet_ntoa(client->addr.sin_addr),
        client->addr.sin_port
    );

    pthread_t thread;
    if (pthread_create(&thread, NULL, process, client) != 0) {
      perror("failed to create thread");
      close(client->sock);
      free(client);
      continue;
    }
    pthread_detach(thread);
  }

  close(server.sock);
}
