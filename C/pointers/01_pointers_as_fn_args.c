#include <stdio.h>

void increment(int *a) { *a += 1; }

int main() {
  int a = 10;
  increment(&a);

  int *pa = &a;
  increment(pa);

  printf("a = %d\n", a);

  return 0;
}
