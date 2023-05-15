#include <stdio.h>

/*
We know when passing a value to a function, the value is copied. So if we need
to access that value we need to pass a pointer to  the value.

When passing an array variable to a function, the array is NOT copied.
Instead, a pointer to the array is passed. i.e the address of the first element

So it is not possible to know the size of the array inside the function since
the array is not copied. We need to pass the size of the array as a separate
argument.
*/

int sum(int a[], int size) { // int* a it is passed by reference
  int i, n = 0;
  /* int size = sizeof(a) / sizeof(a[0]);
  printf("SUM - Size of a = %ld, size of a[0] = %ld\n", sizeof(a),
         sizeof(a[0])); */

  for (i = 0; i < size; i++) {
    n += a[i];
  }

  return n;
}

void doubler(int a[], int size) {
  for (int i = 0; i < size; i++) {
    a[i] *= 2;
    // a[i] = 2 * a[i];
  }
}

int main(int argc, char **argv) {
  // here a is a pointer to the first element of the array
  int a[] = {1, 2, 3, 4, 5};
  // a = &a[0]

  // sizeof(a) = 5 * sizeof(int) = 5 * 4 = 20
  // sizeof(a[0]) = sizeof(int) = 4
  // 20 / 4 = 5 elements
  int size = sizeof(a) / sizeof(a[0]);
  int total = sum(a, size);
  printf("Sum = %d\n", total);

  doubler(a, size);
  for (int i = 0; i < size; i++) {
    printf("%d ", a[i]);
  }

  // printf("MAIN - Size of a = %ld, size of a[0] = %ld\n", sizeof(a),
  //        sizeof(a[0]));

  return 0;
}
