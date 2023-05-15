#include <stdio.h>
#include <stdlib.h>

// Arrays

int main() {
  // define an arary of known size
  int arr[5];
  // or
  // int arr[] = {0, 1, 2, 3, 4};

  // populate the array
  for (int i = 0; i < 5; i++) {
    arr[i] = i;
  }

  // print the 3rd element
  printf("arr[2] = %d\n", arr[2]);

  // Two dimensinal arrays (to reprenst a matrix)
  int matrix[3][3] = {
    {1, 2, 3}, // row 1 index 0
    {4, 5, 6}, // row 2 index 1
    {7, 8 ,9} // row 3 index 2
  };

  // get number 5
  printf("matrix[1][1] = %d\n", matrix[1][1]);



  return 0;
}
