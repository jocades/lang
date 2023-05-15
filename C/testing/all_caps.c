#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

bool is_uppercase(const char *source) {
  // loop to the end of the string
  while (*source) { // if the value is '\0'
    if (islower(*source)) {
      return false;
    }
    source++;
  }
  return true;
}

int main() {
  const char *one = "c";
  const char *two = "C";

  printf("%b\n", is_uppercase(one));
  printf("%b\n", is_uppercase(two));

  return 0;
}
