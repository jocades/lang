#ifndef POINT_H
#define POINT_H

class Point {
 private:
  int x, y;

 public:
  explicit Point(int x, int y);
  int get_x() const;
  int get_y() const;
  void display() const;
};

#endif  // !POINT_H
