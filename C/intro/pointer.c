#include <stdio.h>
#include <stdlib.h>

// THE C PROGRAMMING LANGUAGE - FIRST STEPS
// Allocating memory for a pointer

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


