#include <iostream>
#include <memory>

using namespace std;

constexpr double PI = 3.141592653589793238462643383279502884197;

class Shape {
 public:
  virtual void draw() const = 0;
  virtual double area() const = 0;
  virtual ~Shape() = default;
};

class Square : public Shape {
 private:
  double l, h;

 public:
  Square(double l, double h) : l(l), h(h) {}

  void draw() const override {
    cout << "Drawing Square\n";
  }

  double area() const override {
    return l * h;
  }
};

class Circle : public Shape {
 private:
  double d;

 public:
  Circle(double d) : d(d) {}

  void draw() const override {
    cout << "Drawing Circle\n";
  }

  // r^2 = (d/2)^2 = d^2/4
  double area() const override {
    // return PI * d * d / 4;
    double r = d / 2;
    return PI * r * r;
  }
};

void render(const Shape& shape) {
  shape.draw();
}

int main() {
  // Reserve space for 2 elements in the vector (like Rust's Vec::with_capacity)
  vector<std::unique_ptr<Shape>> shapes;
  shapes.reserve(2);

  // Emplace the elements (no need for pre-constructed objects)
  shapes.emplace_back(make_unique<Square>(5, 10));  // Directly constructs in place
  shapes.emplace_back(make_unique<Circle>(10));

  for (const auto& shape : shapes) {
    shape->draw();
    cout << "Area=" << shape->area() << '\n';
  }
}
