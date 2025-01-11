#ifndef server_h
#define server_h

#include <netinet/in.h>

#define BUF_SIZE 1024

typedef struct {
  int sock;
  struct sockaddr_in addr;
  int max_connections;
} Server;

typedef struct {
  int sock;
  struct sockaddr_in addr;
  char buf[BUF_SIZE];
} Client;

typedef void (*ConnectionCallback)(Client* client);

void serve(Server* server, uint16_t port, ConnectionCallback callback);

#endif  // !server_h
