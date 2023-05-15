#include <stdio.h>
#include <stdlib.h>

/*
-- MEMORY --

Address = location of a variable(memory) in memory (where that memory lives)
Value = the data(value) stored in that location (int, char, float, etc)
address | value
0x1000 | 4 -- int x = 4;
0x1004 | 0x1000 -- int *pX = &x; (saving the address of x in ptr), * means this var is a pointer, & means the address of x not the value
*/

int main() {
  int x = 4;
// <integer> <variable name> = <value>

  int *pX = &x;
/*
<integer> <pointer name> = <address>
'integer pointer named pX is set to the address of x'

 - * (the dereference operator):
'when the asterisk is placed after the data type it means that the variable is a pointer'
'when the asterisk is placed before the variable name it dereferences the pointer meaning that it returns the value stored at the address'

 - & (the address of):
 'when the ampersand is placed before a variable name it returns the address of that variable'
 'when the ampersand is placed before a pointer name it returns the address stored in that pointer'


By using a pointer we can access x by reference instead of by value.
 */

  int y = *pX;
  // (dereferencing pX to get the value stored at the address)
  // 'y is set to the value pointed to by pX'

/*
But why does this matter?
- Pointers allow us to access variables by reference instead of by Value
- Pointers allow us to dynamically allocate memory
- Pointers allow us to pass variables by reference to functions
- Pointers allow us to create complex data structures
- Pointers allow us to create and manipulate strings

When to use pointers?
- When you need to dynamically allocate memory i.e. An unkown array size or a large array
- When you need to pass a variable by reference to a function i.e. You want to change the value of a variable in a function
- When you need to create a complex data structure i.e. A linked list or a tree
- When you need to create or manipulate a string i.e. You want to change the value of a string in a function
*/

  printf("x = %d\n", x);
  printf("y = %d\n", y);
  printf("pX = %p\n", pX);
  printf("*pX = %d\n", *pX);
  printf("&x = %p\n", &x);
  printf("&pX = %p\n", &pX);

  return 0;
}
