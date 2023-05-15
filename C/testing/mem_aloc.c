#include <stdio.h>
#include <stdlib.h>

// THE C PROGRAMMING LANGUAGE - FIRST STEPS

// Allocating memory for a pointer
// Pointers are variables that store the memory address of another variable.

/*
 When you allocate memory using malloc() or calloc(), 
 the operating system reserves a block of memory for your program.
 This block of memory is typically called the heap.
 The malloc() function allocates a single block of memory in the heap.
 The calloc() function allocates multiple blocks of memory in the heap.

  Once you have allocated memory on the heap, you can use it to store data.
  You can access this memory using pointers, which are variables that store the memory address of the allocated block.
  Pointers allow you to manipulate data stored in memory and pass it between functions.
*/

int main() {
  int* ptr;
  int size = 5;

  ptr = (int*) malloc(size * sizeof(int));

  if (ptr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  for (int i = 0; i < size; i++) {
    ptr[i] = i;
  }

  printf("Array values: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", ptr[i]);
  }

  free(ptr);
  return 0;
}


