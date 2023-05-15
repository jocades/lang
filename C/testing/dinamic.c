#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int n;
  printf("Enter array size: \n");
  scanf("%d", &n);

  int *p = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    p[i] = i + 1;
  }

  // free(p);
  // p[2] = 50; // accessing freed memory (accessing the unknown)

  int *px = (int *)realloc(p, n * 2 * sizeof(int));
  printf("Prev block address = %p, new address = %p\n", p, px);

  for (int i = 0; i < n; i++) {
    printf("%d ", p[i]);
  }
  printf("\n");

  for (int i = 0; i < n * 2; i++) {
    printf("%d ", px[i]);
  }
  printf("\n");

  char *str = (char *)malloc(sizeof(char) * 5);
  printf("&str: %d\n", str);
  str = "Jordi";

  return 0;
}
