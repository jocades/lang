#include <stdio.h>

// int = 4 bytes
// char = 1 byte
// float = 4 bytes
// double = 8 bytes
// long = 8 bytes
// unsigned = 4 bytes

int main(int argc, char **argv) {

  /*
  4 bytes, 32 bits
  8bit max = 2^8 - 1 = 255
  16bit max = 2^16 - 1 = 65535
  1025 = 2^10 + 1:

   byte 3   byte 2   byte 1   byte 0
  00000000 00000000 00000100 00000001
  |
  the left most bit is the SIGN BIT, 0 = positive, 1 = negative
  */
  int a = 1025;
  int *p = &a;

  printf("Size of integer is %ld bytes\n", sizeof(int));
  // Look at 4 bytes starting at the address pa points to
  printf("Address = %p, value = %d\n", p, *p);
  // If we inc the int pointer, it will look for the NEXT 4 bytes
  printf("Address = %p, value = %d\n", p + 1, *(p + 1));

  // since char is 1 byte, p0 points to the first byte of 'a'
  // (byte 0) = 00000001 = 1
  char *p0 = (char *)p; // Cast pa to a char pointer

  printf("Size of char is %ld bytes\n", sizeof(char));
  printf("Address = %p, value = %d\n", p0, *p0);

  // If we inc the char pointer, it will look for the NEXT byte
  // (byte 1) = 00000100 = 4
  printf("Address = %p, value = %d\n", p0 + 1, *(p0 + 1));

  // We can also increment the pointer like so:
  a++; // incrementing the pointer by one unit increments the address by the
       // size of the data type

  // Void pointer - Generic pointer
  void *p1;
  p1 = p;

  printf("Address = %p\n", p1);

  return 0;
}
