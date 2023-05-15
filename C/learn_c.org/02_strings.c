#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Strings

int main() {
  // strings in C are arrays of characters
  char *name = "John";
  /*
  This method creates a string which we can only use for reading.
  If we wish to define a string which can be manipulated,
  we will need to define it as a local character array:
   */
  char other[] = "John";
  // which is the same as:
  // char name[5] = {'J', 'o', 'h', 'n', '\0'};
  // '\0' is the null terminator which indicates the end of the string so we
  // need one more character than the number of characters in the string.

  int age = 27;

  printf("%s is %d years old.\n", name, age);

  // String length
  // The strlen() function returns the length of a string. Included in the
  // library string.h
  char *surname = "Doe";
  printf("The length of the string %s is %d.\n", surname, strlen(surname));

  // Compare  strings
  // The strncmp() function compares two strings and returns 0 if they are
  // equal. strcpm() is not recommended because it can cause buffer overflows.
  // args = (string1, string2, max number of characters to compare)

  if (strncmp(name, "John", 4) == 0) {
    printf("Hello, John!\n");
  } else {
    printf("You are not John. Go away.\n");
  }

  // String concatenation
  // The strncat() function concatenates two strings. Included in the library
  // string.h args = (destination, source, max number of characters to
  // concatenate)
  char dest[20] = "Hello";
  char src[20] = "World";
  strncat(dest, src, 3);
  printf("%s\n", dest);
  // strncat(dest, src, 20);
  // printf("%s\n", dest);
  return 0;
}
