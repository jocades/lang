
#include <stdio.h>

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  while (--argc > 0) {
    printf("%s ", argv[argc]);
  }
  printf("\n");

  return 0;
}
