#include <stddef.h>

int buf[3];
size_t cur = 0;

int* next() {
  cur = (cur + 1) % 3;
  return &buf[cur];
}

int main() {}
