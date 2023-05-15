#include <stdio.h>
#include <stdlib.h>

/*
Assuming you now understand pointers and functions, you are aware that
function arguments are passed by value, by which means they are copied in and
out of functions.

But what if we pass pointers to values instead of the values themselves?
This will allow us to give functions control over the variables and structures
of the parent functions and not just a copy of them, thus directly reading and
writing the original object.
*/

// This will not work:
void add_one(int n) {
  // n is a local variable which only exists within the function scope
  n++; // therefore incrementing it has no effect
}

// This will work:
void add_one_ptr(int *n) {
  // n is a pointer here which points to a memory-address outside the functino
  // scope
  (*n)++; // this will effectively increment the value of n
}
/*
 The difference is that the second version of addone receives a pointer to the
 variable n as an argument, and then it can manipulate it, because it knows
 where it is in the memory.
 */

// Pointers to structures
typedef struct {
  int x;
  int y;
} point;

/*
Let's say we want to create a function which moves a point forward in both x and
y directions, called move. Instead of sending two pointers, we can now send only
one pointer to the function of the point structure:
*/

void move(point *p) {
  (*p).x++;
  (*p).y++;
}

/*
 However, if we wish to dereference a structure and access one of it's internal
 members, we have a shorthand syntax for that, because this operation is widely
 used in data structures. We can rewrite this function using the following
 syntax:
*/

void move_one(point *p) {
  p->x++;
  p->y++;
}

int main() {
  int n = 0;
  printf("Before: %d\n", n);
  add_one(n);
  printf("After: %d\n", n);

  printf("Before: %d\n", n);
  add_one_ptr(&n);
  printf("After: %d\n", n);
}
