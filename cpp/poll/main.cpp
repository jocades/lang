#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <cstdio>
#include <string>

const uint16_t PORT = 8000;
const int MAX_EVENTS = 64;

void diep(const char* s) {
  perror(s);
  exit(EXIT_FAILURE);
}

int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) diep("socket()");

  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    diep("setsockopt()");
  }

  sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port = htons(PORT),
    .sin_addr = {.s_addr = INADDR_ANY},
  };

  if (bind(sockfd, (sockaddr*)&addr, sizeof(addr))) {
    diep("bind()");
  }

  if (listen(sockfd, SOMAXCONN)) diep("listen()");

  int kq = kqueue();
  if (kq == -1) diep("kqueue()");

  // Register the server socket to get notified on incoming connections.
  struct kevent ev;
  EV_SET(&ev, sockfd, EVFILT_READ, EV_ADD, 0, 0, nullptr);

  if (kevent(kq, &ev, 1, nullptr, 0, nullptr) == -1) {
    diep("kevent() register server");
  }

  std::array<struct kevent, MAX_EVENTS> events;

  while (true) {
    int nev = kevent(kq, nullptr, 0, events.data(), MAX_EVENTS, nullptr);
    if (nev == -1) diep("kevent() wait");

    for (int i = 0; i < nev; i++) {
      int fd = events[i].ident;

      if (events[i].flags & EV_EOF) {
        printf("CLIENT DC (fd %d)\n", fd);
        close(fd);
        continue;
      }

      if (fd == sockfd) {
        int confd = accept(sockfd, nullptr, nullptr);
        if (confd == -1) {
          perror("accept()");
          continue;
        }
        printf("CLIENT CON (fd %d)\n", confd);

        EV_SET(&ev, confd, EVFILT_READ, EV_ADD, 0, 0, nullptr);
        if (kevent(kq, &ev, 1, nullptr, 0, nullptr)) {
          perror("kevent() register client");
          close(confd);
        }
      } else if (events[i].filter == EVFILT_READ) {
        std::array<char, 1024> buf;
        ssize_t n = read(fd, buf.data(), buf.size());
        if (n <= 0) {
          // EOF or error
          printf("CLIENT DC (fd %d)\n", fd);
          close(fd);
        } else {
          printf("READ %zd (fd %d)\n", n, fd);
          std::string res = "echo: " + std::string(buf.data(), n);
          ssize_t o = write(fd, res.data(), res.size());
          printf("WRITE %zd (fd %d)\n", o, fd);
        }
      }
    }
  }

  return 0;
}
