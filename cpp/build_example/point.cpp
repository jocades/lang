#include "point.h"

#include <iostream>
using namespace std;

Point::Point(int x, int y) : x(x), y(y) {}

int Point::get_x() const {
  return x;
}

int Point::get_y() const {
  return y;
}

void Point::display() const {
  cout << "Coords: (" << x << ", " << y << ")" << endl;
}
