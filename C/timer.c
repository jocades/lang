#include <stdio.h>
#include <time.h>
#include <unistd.h>

void callback() {
  printf("2 seconds passed\n");
}

#define now() ((double)clock() / CLOCKS_PER_SEC)

void timer(double interval, void (*callback)(void)) {
  double start = now();
  for (;;) {
    double now = now();
    if (now - start >= interval) {
      start = now;
      callback();
    }
  }
}

int main() {
  /* timer(2.0, callback); */
  int n = ({
    printf("hello\n");
    1;
  });

  printf("%d\n", n);
  return 0;
}
