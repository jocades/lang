#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* test_get =
    "GET /index.html HTTP/1.1\r\n"
    "Host: localhost:8000\r\n"
    "\r\n";

char* test_post =
    "POST /index.html HTTP/1.1\r\n"
    "Host: localhost:8000\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: 27\r\n"
    "\r\n"
    "{\"name\":\"Bob\",\"age\":25}";

typedef struct {
  char method[8];
  char path[256];
  char* body;
  size_t body_length;
} Request;

bool parse_http_request(const char* data, Request* req) {
  /* const char* headers_end = strstr(data, ) */
  return true;
}

Request* new_request() {
  Request* req = malloc(sizeof(Request));
  if (!req) {
    fprintf(stderr, "failed to allocated request");
    exit(EXIT_FAILURE);
  }
  req->body_length = 0;
  return req;
}

int main() {
  Request* req = new_request();
  if (!parse_http_request(test_get, req)) {
    fprintf(stderr, "failed to parse http request\n");
    return EXIT_FAILURE;
  }
  printf("method=%s path=%s\n", req->method, req->path);

  char* ptr = test_get;
  while (*ptr) {
    printf("%c", *ptr);
    ptr++;
  }
}
