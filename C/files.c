#include <stdio.h>
#include <string.h>

int main() {
  FILE* f;
  size_t offset;

  f = fopen("data", "w+");

  offset = ftell(f);
  printf("offset = %zu\n", offset);

  char* text = "foobarbaz";
  fwrite(text, 1, strlen(text), f);

  offset = ftell(f);
  printf("offset = %zu\n", offset);

  fseek(f, 0, SEEK_SET);
  offset = ftell(f);
  printf("offset = %zu\n", offset);

  char buf[1024];

  size_t r = fread(buf, 1, 3, f);

  printf("r = %zu\n", r);
  offset = ftell(f);
  printf("offset = %zu\n", offset);

  buf[r] = '\0';
  printf("buf = %s\n", buf);

  return 0;
}
