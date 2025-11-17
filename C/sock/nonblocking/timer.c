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

int main() {
  int kq = kqueue();
  if (kq == -1) {
    err(EXIT_FAILURE, "failed to open kq");
  }

  struct kevent ev = {
    .ident = 1,
    .filter = EVFILT_TIMER,
    .flags = EV_ADD,
    .data = 2,
    .fflags = NOTE_SECONDS,
  };

  if (kevent(kq, &ev, 1, NULL, 0, NULL) == -1) {
    err(EXIT_FAILURE, "failed to register timer event");
  }

  struct kevent out;
  int count = 0;
  for (;;) {
    int nev = kevent(kq, NULL, 0, &out, 1, NULL);
    if (nev == -1) {
      err(EXIT_FAILURE, "failed to wait");
    }
    count++;
    printf("Timer fired %d!\n", count);
    print_kevent(&out);
  }

  return 0;
}
