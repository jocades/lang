#include <stdio.h>

#define PRINT(x, ...) printf(x, ##__VA_ARGS__)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
/* #define CONCAT(name) (#name##"added") */
#define S(name) {#name, name##Callback}

typedef struct {
  char* name;
  void (*callback)();
} Struct;

void fooCallback() {}

int main() {
  PRINT("%d", 1);
  eprintf("ERROR: ");

  const char* x =
    "a"
    "b";

  Struct s = S(foo);

  return 0;
}
