#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR(name, type) \
  typedef struct {         \
    type* ptr;             \
    size_t len;            \
    size_t cap;            \
  } name

VECTOR(Vec, int);

/* typedef struct {
  int* ptr;
  size_t len;
  size_t cap;
} Vec; */

void initVec(Vec* vec) {
  vec->ptr = NULL;
  vec->len = 0;
  vec->cap = 0;
}

void freeVec(Vec* vec) {
  free(vec->ptr);
  initVec(vec);
}

void printVec(Vec* vec) {
  printf("ptr=%p len=%zu cap=%zu\n", vec->ptr, vec->len, vec->cap);
  for (size_t i = 0; i < vec->len; i++) {
    printf("index=%zu value=%d\n", i, vec->ptr[i]);
  }
}

void append(Vec* vec, int val) {
  if (vec->cap < vec->len + 1) {
    size_t cap = vec->cap;
    vec->cap = cap < 8 ? 8 : cap * 2;
    vec->ptr = realloc(vec->ptr, vec->cap * sizeof(*vec->ptr));
  }
  vec->ptr[vec->len] = val;
  vec->len++;
}

int main() {
  Vec vec;
  initVec(&vec);

  append(&vec, 1);
  append(&vec, 2);
  append(&vec, 3);

  printVec(&vec);
  freeVec(&vec);
  printVec(&vec);

  return 0;
}
