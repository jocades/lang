#include <stdint.h>
#include <stdio.h>

typedef enum {
  A = 1,
  B = 1 << 1,
  C = 1 << 2,
  D = 1 << 3,
} Opt;

int main() {
  uint8_t opts = A | C | D;

  if (opts & A) printf("a\n");
  if (opts & B) printf("b\n");
  if (opts & C) printf("c\n");
  if (opts & D) printf("d\n");

  return 0;
}
