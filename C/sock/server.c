#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUF_SIZE 1024

typedef struct {
  int sock;
  char buf[BUF_SIZE];
} Client;

void* process(Client* client) {
  while (true) {
    int n = read(client->sock, client->buf, BUF_SIZE);
    if (n <= 0) {
      printf("Client closed connection\n");
      break;
    }

    printf("Received: %s", client->buf);
    send(client->sock, client->buf, n, 0);
    memset(client->buf, 0, n);
  }

  close(client->sock);

  return NULL;
}

typedef struct {
  int sock;
  struct sockaddr_in addr;
  socklen_t addrlen;
} Server;

void serve(Server* server) {
  // Create socket file descriptor
  server->sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server->sock < 0) {
    perror("failed to create socket");
    exit(EXIT_FAILURE);
  }

  // Set socket options (on macOS cannot use bitwise OR to set socket options,
  // hence we need 2 separate calls)
  int opt = 1;
  int err =
      setsockopt(server->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (err != 0) {
    perror("failed to set SO_REUSEADDR");
    exit(EXIT_FAILURE);
  }

  // Configure address structure
  server->addrlen = sizeof(server->addr);
  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = INADDR_ANY;
  server->addr.sin_port = htons(PORT);

  // Bind socket to port
  err = bind(server->sock, (struct sockaddr*)&server->addr, server->addrlen);
  if (err < 0) {
    perror("failed to bind socket");
    exit(EXIT_FAILURE);
  }

  // Listen for connections
  err = listen(server->sock, 3);
  if (err < 0) {
    perror("failed to listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening @ localhost:%d\n", PORT);
}

typedef struct {
  Client* client;
  size_t len;
  size_t cap;
} Clients;

void push(Clients* clients, Client* client) {}

int main() {
  Server server;
  serve(&server);

  Client clients[2];

  while (true) {
    Client client = clients[0];
    client.sock =
        accept(server.sock, (struct sockaddr*)&server.addr, &server.addrlen);
    if (client.sock < 0) {
      perror("failed to accept");
      exit(EXIT_FAILURE);
    }

    printf("New client connected\n");
    process(&client);
  }

  close(server.sock);
}
