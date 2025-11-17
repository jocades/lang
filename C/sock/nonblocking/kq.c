
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include <time.h>

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

void kq_on_stdin() {
  int kq = kqueue();
  if (kq == -1) {
    err(EXIT_FAILURE, "failed to open kq");
  }

  struct kevent ev = {0};
  ev.ident = 0;
  ev.filter = EVFILT_READ;
  ev.flags = EV_ADD;

  if (kevent(kq, &ev, 1, NULL, 0, NULL) == -1) {
    err(EXIT_FAILURE, "failed to register stdin");
  }

  struct kevent out;
  struct timespec ts = {2};

  int nev = kevent(kq, NULL, 0, &out, 1, &ts);
  if (nev == 0) {
    printf("kevent timed out\n");
  } else {
    print_kevent(&out);
    int can_read = out.filter & EVFILT_READ;
    if (can_read) {
      printf("Fd %d is ready to read\n", (int)ev.ident);
    } else {
      printf("unexpected event ocurred: %d\n", out.filter);
    }
  }
}

int main() {
  kq_on_stdin();
  return 0;
}
