#include <stdio.h>
#include <stdlib.h>

/*
C structures are special, large variables which contain several named variables
inside. Structures are the basic foundation for objects and classes in C.
Structures are used for:
- Serialization of data
- Passing multiple arguments in and out of functions through a single argument
- Data structures such as linked lists, binary trees, and more
*/

/*
struct point {
  int x;
  int y;
}
*/
;

/*
Typedefs allow us to define types with a different name - which can come in
handy when dealing with structs and pointers. In this case, we'd want to get rid
of the long definition of a point structure. We can use the following syntax to
remove the struct keyword from each time we want to define a new point:
*/

typedef struct {
  int x;
  int y;
} point;

/*
 Structures can also hold pointers - which allows them to hold strings,
 or pointers to other structures as well - which is their real power.
 For example, we can define a vehicle structure in the following manner:
 */

typedef struct {
  char *brand;
  int model;
} vehichle;

void draw(point p) { printf("Drawing point at %d, %d\n", p.x, p.y); }

int main() {
  point p;
  p.x = 10;
  p.y = 20;
  draw(p);

  vehichle my_car;
  my_car.brand = "Ford";
  my_car.model = 2007;
  printf("My car is a %s from %d\n", my_car.brand, my_car.model);

  return 0;
}
