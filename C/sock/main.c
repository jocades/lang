#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "log.h"
#include "server.h"

#define BUF_SIZE 1024

void handle_connection(Connection* conn) {
  char buf[BUF_SIZE];

  while (true) {
    int n = read(conn->sock, buf, BUF_SIZE);
    if (n <= 0) {
      info("Client disconnected %d", conn->peer.sin_port);
      break;
    }

    debug("Received: %s", buf);
    send(conn->sock, buf, n, 0);
    memset(buf, 0, n);
  }
}

int main() {
  init_logger(LOG_TRACE);

  Server server = {.max_connections = 3};
  serve(&server, 8000, handle_connection);
}
