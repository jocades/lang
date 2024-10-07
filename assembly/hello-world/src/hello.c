#include <stdio.h>

extern int my_function(int a, int b);

int main() {
  int a = 4;
  int b = 5;
  printf("Calling assembly function my_function with x0=%d and x1=%d results "
         "in %d\n",
         a, b, my_function(a, b));
  return (0);
}
