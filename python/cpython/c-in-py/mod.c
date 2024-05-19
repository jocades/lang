#include <stdio.h>

void hello() {
  printf("Hello, World!\n");
}

int add(int a, int b) {
  return a + b;
}

// def fib(n: int) -> list[int]:
//     cache = [0, 1]
//     for i in range(2, n):
//         cache.append(cache[i - 1] + cache[i - 2])
//
//     return cache


int fib(int n) {
  if (n == 0) {
    return 0;
  }

  if (n == 1) {
    return 1;
  }

  int a = 0;
  int b = 1;
  for (int i = 2; i < n; i++) {
    int c = a + b;
    a = b;
    b = c;
  }

  return b;
}
