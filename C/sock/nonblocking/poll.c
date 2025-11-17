#include <stdio.h>

#include "poll.h"

int main() {
  struct pollfd pfds[1];

  pfds[0].fd = 0;  // stdin
  pfds[0].events = POLLIN;

  printf("Hit RETURN or wait for 2.5 seconds for timeout\n");

  int nev = poll(pfds, 1, 2500);

  if (nev == 0) {
    printf("Poll timed out!\n");
  } else {
    int pollin_happened = pfds[0].revents & POLLIN;

    if (pollin_happened) {
      printf("Fd %d is ready to read\n", pfds[0].fd);
    } else {
      printf("Unexpected event ocurred: %d\n", pfds[0].revents);
    }
  }

  return 0;
}
