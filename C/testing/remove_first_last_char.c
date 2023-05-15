#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_char(char *dst, const char *src) {

  int len = strlen(src);
  strncpy(dst, src + 1, len - 1);
  dst[len - 1] = '\0';

  return dst;
}

int main() {

  char *strings[] = {"eloquent", "country", "person", "place", "ok"};
  // char* expected[] = {"loquen", "ountr", "erso", "lac", ""};

  char *name = "jordi";
  int len = strlen(name);

  char *new_name = malloc(sizeof(char) * len);
  strncpy(new_name, name + 1, len - 1);
  new_name[len - 1] = '\0';

  printf("Original string: %s\n", name);
  printf("New string: %s\n", new_name);
  free(new_name); // free the memory

  size_t str_len = sizeof(strings) / sizeof(strings[0]);
  printf("the len of the str array is %lu\n", str_len);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < strlen(strings[i]); j++) {
      printf("%c", strings[i][j]);
    }
    printf("\n");
  }

  size_t str = sizeof(strings[0]);
  printf("the sized of the 1st str is %lu\n", str);

  int n = 5;
  size_t size = sizeof(n);
  printf("int 5 size: %lubytes\n", sizeof(size));

  int numbers[] = {2, 4, 6, 8};
  printf("%p\n", *&numbers + 1);
  printf("numbers array size: %lubytes\n", sizeof(numbers));

  size_t length = sizeof(numbers) / sizeof(numbers[0]);
  printf("the len of the array is %lu\n", length);
  return 0;
}
