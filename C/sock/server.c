#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUF_SIZE 1024

int main() {
  int sock_fd, err;
  int opt = 1;

  // Create socket file descriptor
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    perror("failed to create socket");
    exit(EXIT_FAILURE);
  }

  // Set socket options (on macOS cannot use bitwise OR to set socket options,
  // hence we need 2 separate calls)
  err = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (err != 0) {
    perror("failed to set SO_REUSEADDR");
    exit(EXIT_FAILURE);
  }
  err = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
  if (err != 0) {
    perror("failed to set SO_REUSEPORT");
    exit(EXIT_FAILURE);
  }

  // Configure address structure
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);

  // Bind socket to port
  err = bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
  if (err < 0) {
    perror("failed to bind socket");
    exit(EXIT_FAILURE);
  }

  // Listen for connections
  err = listen(sock_fd, 3);
  if (err < 0) {
    perror("failed to listen");
    exit(EXIT_FAILURE);
  }

  printf("Listening @ localhost:%d\n", PORT);

  int client_fd;
  char buf[BUF_SIZE];

  while (true) {
    // Accept incoming connections (this is blocking)
    client_fd = accept(sock_fd, (struct sockaddr*)&addr, &addr_len);
    if (client_fd < 0) {
      perror("failed to accept");
      exit(EXIT_FAILURE);
    }

    printf("New client connected\n");

    // Read client message and echo it back
    while (true) {
      int n = read(client_fd, buf, BUF_SIZE);
      if (n <= 0) {
        printf("Client closed connection\n");
        break;
      }

      printf("Recv: %s", buf);
      send(client_fd, buf, n, 0);
      memset(buf, 0, n);
    }

    close(client_fd);
  }

  close(sock_fd);
}
