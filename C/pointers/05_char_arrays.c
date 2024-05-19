#include <stdio.h>
#include <string.h>

/*
Size of character array (string) >= n of chars in string + 1
"John" size >= 4 + 1 = 5
 * */

void print(char *c) { // same as char c[] but when an array is passed as an arg
                      // to a function, it is passed by reference
  while (*c) {        // it will stop when it reaches the null character
    printf("%c", *c);
    c++;
  }
  printf("\n");
}

// print array of strings (string = array of chars)
void print2(char **c) { // same as char *c[]
  int i = 0;
  while (c[i] != NULL) {
    printf("%s\n", c[i]);
    i++;
  }
}

int main(int argc, char **argv) {
  char a[20];
  a[0] = 'J';
  a[1] = 'o';
  a[2] = 'h';
  a[3] = 'n';
  a[4] = '\0';
  printf("Size in bytes of a = %ld\n", sizeof(a));
  printf("%s\n", a); // Even tho the arr is size 20, only chars until \0 are
                     // printed

  int len = strlen(a);
  printf("Length of string = %d\n", len);

  char b[] = "John"; // Null character is automatically added when using ""
                     // Also the size of the array is automatically calculated
  printf("Size in bytes of b = %ld\n", sizeof(b));
  printf("%s\n", b);

  // 1. Arrays and pointers are different types that are used in similar manner
  char c[6] = "Hello"; // 6 bytes
  char *pc = c;

  // we can do something like this even though c is an array
  pc = c; // pc = &c[0] (valid)

  // 2. Arrays are always passed to a function by reference
  print(c); // print(&c[0])

  // 3. Array of strings
  char *names[] = {"John", "Jane", "Jack", "Jim", "Jill", NULL};
  print2(names);

  // When using a string literal
  char str[6] = "Hello"; // string gets stored in the space
                         // for the array (stack)
  char *str2 = "Hello";  // string gets stored as compile time constant
                         // (code section read only memory)

  return 0;
}

// it doesnt know the size of the array just the base address
/* void print(char *c) {
  int i = 0;
  while (c[i] != '\0') {
    printf("%c", c[i]);
    i++;
  }
  printf("\n");
} */

/* void print(char *c) {
  while (*c != '\0') {
    printf("%c", *c);
    c++;
  }
  printf("\n");
} */
