#include <stdio.h>
#include <stdlib.h>
/*
Dynamic allocation of memory is a very important subject in C. It allows
building complex data structures such as linked lists. Allocating memory
dynamically helps us to store data without initially knowing the size of the
data in the time we wrote the program.

To allocate a chunk of memory dynamically, we need to have a pointer ready to
store the location of the newly allocated memory. We can access memory that was
allocated to us using that same pointer, and we can use that pointer to free the
memory again, once we have finished using it.

Let's assume we want to dynamically allocate a person structure. The person is
defined like this:
*/

typedef struct {
  char *name;
  int age;
} person;

int main() {
  // To allocate a new person in the myperson argument, we use the following
  // syntax:

  person *myperson = (person *)malloc(sizeof(person));
  /*
   This tells the compiler that we want to dynamically allocate just enough to
  hold a person struct in memory and then return a pointer of type person to the
  newly allocated data. The memory allocation function malloc() reserves the
  specified memory space. In this case, this is the size of person in bytes.

  The reason we write (person *) before the call to malloc() is that malloc()
  returns a "void pointer," which is a pointer that doesn't have a type. Writing
  (person *) in front of it is called typecasting, and changes the type of the
  pointer returned from malloc() to be person. However, it isn't strictly
  necessary to write it like this as C will implicitly convert the type of the
  returned pointer to that of the pointer it is assigned to (in this case,
  myperson) if you don't typecast it.

  Note that sizeof is not an actual function, because the compiler interprets it
  and translates it to the actual memory size of the person struct.
 */

  // To access the person's members, we can use the -> notation:
  myperson->name = "John";
  myperson->age = 27;

  // After we are done using the dynamically allocated struct, we can release it
  // using free:
  free(myperson);
  /*
  Note that the free does not delete the myperson variable itself, it simply
  releases the data that it points to. The myperson variable will still point
  to somewhere in the memory - but after calling myperson we are not allowed
  to access that area anymore. We must not use that pointer again until we
  allocate new data using it.
  */

  // ARRAYS AND POINTERS
  char c = 'A';
  char *pc = &c;

  char vowels[] = {'A', 'E', 'I', 'O', 'U'};
  char *pvowels = vowels;

  int i;

  // print the addresses
  for (i = 0; i < 5; i++) {

    printf("&vowels[%d]: %p, pvowels + %d: %p, vowels + %d: %p\n", i,
           &vowels[i], i, pvowels + i, i, vowels + 1);
  }

  // print the values
  for (i = 0; i < 5; i++) {
    printf("vowels[%d]: %c, *(pvowels + %d): %c, *(vowels + %d): %c\n", i,
           vowels[i], i, *(pvowels + i), i, *(vowels + i));
  }

  // As we can see we can get the next element in the array by adding 1 to the
  // pointer. Since in the end an array is a continuous block of memory adding 1
  // to the mem-address will point to the next element in the array.

  // DYNAMIC MEMORY ALLOCATION for ARRAYS
  // Allocate memory to store 5 characters
  int n = 5;
  char *pletters = (char *)malloc(n * sizeof(char));

  pletters[0] = 'A';
  pletters[1] = 'B';
  *(pletters + 2) = 'C';
  pletters[3] = 'D';
  *(pletters + 4) = 'E';

  for (i = 0; i < n; i++) {
    printf("%c ", pletters[i]);
  }

  printf("\n");

  // Free the memory, since we don't need it anymore
  free(pletters);

  // DYNAMIC MEMORY ALLOCATION for MULTIDIMENSIONAL ARRAYS
  // Unlike one-dimensional arrays, where we used a pointer, in this case we
  // require a pointer to a pointer.

  int nrows = 2;
  int ncols = 5;
  int j, k;

  // Allocate memory for nrows pointers
  // ** is a pointer to a pointer
  char **pnames = (char **)malloc(nrows * sizeof(char *));

  // For each row, allocate memory for ncols elements
  // which is the same as a table with 5 fields and 2 records
  // we could to it mannaully like this:
  pnames[0] = (char *)malloc(ncols * sizeof(char));
  pnames[1] = (char *)malloc(ncols * sizeof(char));

  // or we could do it in a loop like this:
  // for (j = 0; j < nrows; j++) {
  //   pnames[j] = (char *)malloc(ncols * sizeof(char));
  // }

  // Store names in the allocated memory
  pnames[0][0] = 'A';
  pnames[0][1] = 'E';
  pnames[0][2] = 'I';
  pnames[0][3] = 'O';
  pnames[0][4] = 'U';

  pnames[1][0] = 'a';
  pnames[1][1] = 'e';
  pnames[1][2] = 'i';
  pnames[1][3] = 'o';
  pnames[1][4] = 'u';

  // Print data
  for (j = 0; j < nrows; j++) {
    for (k = 0; k < ncols; k++) {
      printf("%c ", pnames[j][k]);
    }
  }

  printf("\n");

  // Free the memory
  for (j = 0; j < nrows; j++) {
    free(pnames[j]);
  }

  // Free the top-level pointer
  free(pnames);

  return 0;
}
