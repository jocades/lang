#include <stdio.h>
#include <stdlib.h>

int main() {
  int size = 10;
  int *p = (int *)malloc(size * sizeof(int));
  int *q = (int *)calloc(size, sizeof(int));
  int *r = (int *)malloc(size * sizeof(int));

  for (int i = 0; i < size; i++) {
    // p[i] = i;
    // or
    *(p + i) = i;
  }

  p[1] = 10;
  (*p)++;
  p[1]++;
  *(p + 1) = *(p + 1) + 1;
  for (int i = 0; i < size; i++) {
    printf("p[%d] = %d\n", i, p[i]);
  }

  for (int i = 0; i < size; i++) {
    printf("q[%d] = %d\n", i, q[i]);
  }

  free(p);
  free(q);
  free(r);
}
