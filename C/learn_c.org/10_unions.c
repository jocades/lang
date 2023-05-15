#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
C Unions are essentially the same as C Structures, except that instead of
containing multiple variables each with their own memory a Union allows for
multiple names to the same variable. These names can treat the memory as
different types (and the size of the union will be the size of the largest type,
+ any padding the compiler might decide to give it)

So if you wanted to be able to read a variable's memory in different ways, for
example read an integer one byte at a time, you could have something like this:
 */

union intParts {
  int theInt;
  char bytes[sizeof(int)];
};

int main() {
  // Allowing you to look at each byte individually without casting a pointer
  // and using pointer arithmetic:
  union intParts parts;
  parts.theInt = 5968145; // arbitrary number > 255 (1 byte)

  printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n", parts.theInt,
         parts.bytes[0], parts.bytes[1], parts.bytes[2], parts.bytes[3]);

  // vs

  int theInt = parts.theInt;
  printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n", theInt,
         *((char *)&theInt + 0), *((char *)&theInt + 1), *((char *)&theInt + 2),
         *((char *)&theInt + 3));

  // or with array syntax which can be a tiny bit nicer sometimes

  printf("The int is %i\nThe bytes are [%i, %i, %i, %i]\n", theInt,
         ((char *)&theInt)[0], ((char *)&theInt)[1], ((char *)&theInt)[2],
         ((char *)&theInt)[3]);

  /*
  Combining this with a structure allows you to create a "tagged" union
  which can be used to store multiple different types, one at a time.

  For example, you might have a "number" struct, but you don't want to use
  something like this:
  */
  struct operator{
    int intNum;
    float floatNum;
    int type;
    double doubleNum;
  };

  return 0;
}
