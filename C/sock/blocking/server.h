#ifndef server_h
#define server_h

#include <netinet/in.h>

typedef struct {
  int sock;
  struct sockaddr_in addr;
  int max_connections;
} Server;

typedef struct {
  int sock;
  struct sockaddr_in peer;
} Connection;

typedef void (*ConnectionCallback)(Connection* conn);

void serve(Server* server, uint16_t port, ConnectionCallback callback);

#endif  // !server_h
