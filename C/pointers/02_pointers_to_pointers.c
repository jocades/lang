#include <stdio.h>

int main(int argc, char **argv) {
  int a = 10;
  int *pa = &a;
  int **ppa = &pa;

  printf("a = %d\n", a);
  printf("pa = %p\n", pa);
  printf("ppa = %p\n", ppa);
  printf("*ppa = %p\n", *ppa);
  printf("**ppa = %d\n", **ppa);

  return 0;
}
