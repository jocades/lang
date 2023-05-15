#include <stdio.h>
#include <stdlib.h>

int main() {
  /*
   Incrementing a pointer:
   Just like any variable the ++ operation increases the value of that variable.
   In our case here the variable is a pointer hence when we increase its value
   we are increasing the address in the memory that pointer points to.
   */

  int intarray[5] = {10, 20, 30, 40, 50};

  for (int i = 0; i < 5; i++)
    printf("intarray[%d] has value %d - and address @ %x\n", i, intarray[i],
           &intarray[i]);

  int *intpointer = &intarray[3]; // point to the 4th element in the array
  printf("address: %x - has value %d\n", intpointer,
         *intpointer); // print the address of the 4th element

  intpointer++; // now increase the pointer's address so it points to the 5th
                // elemnt in the array
  printf("address: %x - has value %d\n", intpointer,
         *intpointer); // print the address of the 5th element

  return 0;
}
