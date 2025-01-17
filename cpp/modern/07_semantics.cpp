#include <iostream>

using std::cout;

/*
If a class manages resources using raw pointers, we need to follow the Rule of Five:

Destructor.
Copy constructor.
Copy assignment operator.
Move constructor.
Move assignment operator.
*/

class What {
 private:
  int* data;

 public:
  // Constructor
  What(int v) : data(new int(v)) {
    cout << "Construct\n";
  }

  // Copy Constructor
  What(const What& other) : data(new int(*other.data)) {
    cout << "Copy\n";
  }

  // Move Constructor
  What(What&& other) noexcept : data(other.data) {
    other.data = nullptr;
    cout << "Move\n";
  }

  // Copy Assignment Operator
  What& operator=(const What& other) {
    if (this == &other) return *this;  // Self-assignment check
    *data = *other.data;               // Deep copy
    cout << "Copy assignment\n";
    return *this;
  }

  // Move assignment Operator
  What& operator=(What&& other) noexcept {
    if (this == &other) return *this;  // Self-assignment check
    delete data;                       // Free exisiting resource
    data = other.data;                 // Transfer ownership
    other.data = nullptr;
    cout << "Move assignment\n";
    return *this;
  }

  // Destructor
  ~What() {
    delete data;
    cout << "Destructor\n";
  }

  void display() {
    if (data) {
      cout << "Value: " << *data << '\n';
    } else {
      cout << "Data is null\n";
    }
  }
};

void semantics() {
  What o1(10);   // Constructor
  What o2 = o1;  // Copy Constructor
  o2.display();

  What o3 = std::move(o1);  // Move Constructor
  o3.display();
  o1.display();

  What o4(20);
  o4 = o3;  // Copy Assignment
  o4.display();

  What o5(30);
  o5 = std::move(o4);  // Move Assignment
  o5.display();
  o4.display();
}

// New Type Wrapper and how to make it work like Rust's `Deref` trait
template <typename T>
class Wrap {
 private:
  T inner;

 public:
  // Constructor
  explicit Wrap(T v) : inner(std::move(v)) {}

  // Overload the `*` operator (dereference)
  T& operator*() {
    return inner;
  }

  const T& operator*() const {
    return inner;
  }

  // Overlaod the `->` operator (member-acces)
  T* operator->() {
    return &inner;
  }

  const T* operator->() const {
    return &inner;
  }
};

struct Data {
  int x;
  void display() const {
    cout << "Data.x = " << x << '\n';
  }
};

void new_type() {
  Wrap<Data> wrapped(Data{10});

  // Accessing the underlying data seamlessly
  wrapped->display();
  (*wrapped).x = 20;
  wrapped->display();
}

class W {
 public:
  int v;

  W() {
    cout << "W Constructor\n";
  }

  W(W& other) {
    v = other.v;
    cout << "W Copy Constructor\n";
  };

  W(W&& other) noexcept {
    other.v = -1;
    cout << "W Move Constructor\n";
  }
};

class X {
 public:
  W _w;

  X(W& w) : _w(std::move(w)) {
    cout << "X Constructor\n";
  }

  X(W&& w) : _w(std::move(w)) {
    cout << "X Move Constructor\n";
  }
};

W create() {
  W w;
  w.v = 10;
  return w;  // return value optimization (allocated where this function is called)
}

void what() {
  auto w1 = create();
  cout << w1.v << '\n';

  W w2 = w1;
  cout << w2.v << '\n';

  W w3 = std::move(w2);
  cout << w3.v << '\n';
  cout << w2.v << '\n';

  W& w4 = w3;
  w4.v = 20;
  cout << w4.v << '\n';
  cout << w3.v << '\n';
}

int main() {
  semantics();
  new_type();
  what();
}
