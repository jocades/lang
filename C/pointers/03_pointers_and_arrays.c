#include <stdio.h>

int main(int argc, char **argv) {
  int a[] = {2, 4, 5, 8, 1};
  // a = address of the 1st element (base address)
  printf("a = %p\n", a);

  // Address:
  int *p = &a[1]; // a + 1
  printf("p = %p, *p = %d\n", p, *p);

  // Value:
  int val = a[1]; // *(a + 1)
  printf("val = %d\n", val);

  // We can also increment the pointer to access the next element
  // a++; // invalid since a is an array
  p++; // valid since p is a pointer
  printf("p = %p, *p = %d\n", p, *p);

  return 0;
}
