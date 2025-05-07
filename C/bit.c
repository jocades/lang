#include <stdint.h>
#include <stdio.h>

int main() {
  short x = 0x1234;

  uint8_t hi = (x >> 8) & 0xff;
  uint8_t lo = x & 0xff;

  printf("x  = %#x (%d)\n", x, x);
  printf("hi = %#06x (%d)\n", hi, hi);
  printf("lo = %#06x (%d)\n", lo, lo);

  return 0;
}
