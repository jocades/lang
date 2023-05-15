#include <stdio.h>

unsigned int multiply(unsigned int x, unsigned int y) {
  if (x == 1) {
    // terminating case
    return y;
  } else if (x > 1) {
    // recursive step
    return y + multiply(x - 1, y);
  }
  // catch scenario where x is zero
  return 0;
}
// Define a new function called factorial() that will compute the factorial by
// recursive multiplication (5! = 5 x 4 x 3 x 2 x 1). Note that by convention,
// the factorial of 0 is equal to 1 (0! = 1).

int factorial(int n) {
  if (n == 0) {
    return 1;
  } else if (n > 0) {
    return n * factorial(n - 1);
  }
  return 0;
}

int main() {
  printf("3 times 5 is %d\n", multiply(3, 5));

  printf("0! = %i\n", factorial(0));
  printf("1! = %i\n", factorial(1));
  printf("3! = %i\n", factorial(3));
  printf("5! = %i\n", factorial(5));

  return 0;
}
