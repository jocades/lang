#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "log.h"
#include "server.h"

void handle_connection(Client* client) {
  while (true) {
    int n = read(client->sock, client->buf, BUF_SIZE);
    if (n <= 0) {
      info("Client disconnected %d", client->addr.sin_port);
      break;
    }

    debug("Received: %s", client->buf);
    send(client->sock, client->buf, n, 0);
    memset(client->buf, 0, n);
  }
}

int main() {
  init_logger(LOG_TRACE);
  Server server = {.max_connections = 3};
  serve(&server, 8000, handle_connection);
}
