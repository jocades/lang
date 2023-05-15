#include <stdio.h>
#include <stdlib.h>

//Create a function that takes an integer as an argument and returns "Even" for even numbers or "Odd" for odd numbers.

char* even_or_odd(int number) {
  return number % 2 == 0 ? "Even" : "Odd";
}

int main() {
  int number;
  printf("Enter a number: ");
  scanf("%d:", &number);

  printf("%d is %s\n", number, even_or_odd(number));
  return 0;
}
