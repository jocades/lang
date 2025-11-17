#include <arpa/inet.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8000
#define MAX_EVENTS 64
#define MAX_PEERS 5

void panic(const char* s) {
  perror(s);
  exit(1);
}

void cvt(int n, const char* m) {
  if (n == -1) panic(m);
}

int tcp_listener() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  cvt(fd, "failed to open socket");

  int opt = 1;
  cvt(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)), "failed to set socket opts");

  struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port = htons(PORT),
    .sin_addr = {.s_addr = INADDR_ANY}
  };

  cvt(bind(fd, (struct sockaddr*)&addr, sizeof(addr)), "failed to bind socket");
  cvt(listen(fd, SOMAXCONN), "failed to listen");

  return fd;
}

int register_event(int kq, int fd, int16_t filter, uint16_t flags) {
  struct kevent ev = {0};
  ev.ident = fd;
  ev.filter = filter;
  ev.flags = flags;
  return kevent(kq, &ev, 1, NULL, 0, NULL);
}

int get_events(int kq, struct kevent* events) {
  return kevent(kq, NULL, 0, events, MAX_EVENTS, NULL);
}

void add_peer(int peer, int* peers, int* count) {
  // todo: check bounds
  peers[(*count)++] = peer;
  printf("added peer (fd %d); peer_count = %d\n", peer, *count);
}

void remove_peer(int peer, int* peers, int* count) {
  int i = 0;
  for (; i < *count; i++) {
    if (peers[i] == peer) break;
  }
  if (i != MAX_PEERS) {
    peers[i] = peers[--(*count)];
  }
  printf("removed peer (fd %d); peer_count = %d\n", peer, *count);
  close(peer);
}

void on_connection(int listener, int kq, int* peers, int* peer_count) {
  int peer = accept(listener, NULL, NULL);
  if (peer == -1) {
    perror("failed to accept");
    return;
  }

  if (register_event(kq, peer, EVFILT_READ, EV_ADD) == -1) {
    close(peer);
    perror("failed to register peer");
    return;
  }

  add_peer(peer, peers, peer_count);
}

void on_data(int peer, int* peers, int* peer_count) {
  char buf[256];
  int n = read(peer, buf, sizeof(buf));

  if (n <= 0) {
    if (n == 0) {
      printf("client disconnectd\n");
    } else {
      perror("failed to read");
    }
    remove_peer(peer, peers, peer_count);
    return;
  }

  for (int i = 0; i < *peer_count; i++) {
    if (peers[i] != peer) {
      write(peers[i], buf, n);
    }
  }
}
void print_kevent(const struct kevent* ev) {
  printf(
    "kevent {\n"
    "  ident: %d,\n"
    "  filter: %d,\n"
    "  flags: %d,\n"
    "  fflags: %d,\n"
    "  data: %ld,\n"
    "  udata: %p,\n"
    "}\n",
    (int)ev->ident,
    ev->filter,
    ev->flags,
    ev->fflags,
    ev->data,
    ev->udata
  );
}

int main() {
  int listener = tcp_listener();
  printf("Listening on port %d...\n", PORT);

  int kq = kqueue();
  cvt(kq, "failed to open kqueue");

  cvt(register_event(kq, listener, EVFILT_READ, EV_ADD), "failed to register listener");

  struct kevent events[MAX_EVENTS];

  int peers[MAX_PEERS];
  int peer_count = 0;

  for (;;) {
    int nev = get_events(kq, events);
    cvt(nev, "failed to wait for event");
    printf("nev = %d\n", nev);

    for (int i = 0; i < nev; i++) {
      struct kevent* ev = &events[i];
      print_kevent(ev);

      int fd = ev->ident;

      if (ev->flags & EV_EOF) {
        remove_peer(fd, peers, &peer_count);
        continue;
      }

      if (ev->filter == EVFILT_READ) {
        if (fd == listener) {
          on_connection(listener, kq, peers, &peer_count);
        } else {
          on_data(fd, peers, &peer_count);
        }
      }
    }
  }
}
