#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KB(n) (n * 1024)
#define MB(n) (n * 1024 * 1024)

typedef struct {
  uint8_t* buf;
  size_t cap;
  size_t cur;
} Arena;

Arena arena_new(size_t cap) {
  uint8_t* buf = malloc(cap);
  return (Arena){buf, cap, 0};
}

void* arena_alloc(Arena* a, size_t size) {
  uint8_t* slot = a->buf + a->cur;
  a->cur += size;
  if (a->cur >= a->cap) {
    fprintf(stderr, "Arena out of space\n");
    exit(1);
  }
  return slot;
}

void arena_reset(Arena* a) {
  memset(a->buf, 0, a->cur);
  a->cur = 0;
}

void arena_free(Arena* a) {
  free(a->buf);
  a->buf = NULL;
  a->cap = 0;
  a->cur = 0;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "missing size argument\n");
    exit(1);
  }

  char* end;
  size_t size = strtoll(argv[1], &end, 10);
  if (*end != '\0') {
    fprintf(stderr, "invalid number '%s'\n", argv[1]);
    exit(1);
  }

  Arena arena = arena_new(size);

  int* a = arena_alloc(&arena, sizeof(int));
  int* b = arena_alloc(&arena, sizeof(int));
  int* c = arena_alloc(&arena, sizeof(int));
  *a = 10;
  *b = 20;
  *c = 30;

  for (size_t i = 0; i < arena.cur; i += sizeof(int)) {
    printf("%zu = %d\n", i, arena.buf[i]);
  }

  arena_reset(&arena);

  int* d = arena_alloc(&arena, sizeof(int));
  *d = 40;

  for (size_t i = 0; i < arena.cur; i += sizeof(int)) {
    printf("%zu = %d\n", i, arena.buf[i]);
  }

  arena_free(&arena);

  return 0;
}
