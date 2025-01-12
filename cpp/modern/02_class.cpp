#include <cstring>
#include <iostream>
#include <utility>
using namespace std;

/*
A modern C++ class should typically:
- Have a constructor (default, parameterized, and possibly a move constructor).
- Implement move semantics with a move constructor and move assignment operator.
- Implement destructors if necessary (especially for managing dynamic resources).
- Leverage smart pointers for resource management (e.g., std::unique_ptr, std::shared_ptr).
- Use explicit for constructors that should not be implicitly invoked.
- Optionally, define noexcept for methods that are guaranteed not to throw exceptions (for
performance optimization).
*/

class String {
 private:
  char* _data;
  size_t _size;

 public:
  // Default constructor
  String() : _data(nullptr), _size(0) {}

  // Parametrized constructor
  explicit String(const char* str) {
    _size = strlen(str);
    _data = new char[_size + 1];
    strcpy(_data, str);
  }

  // Move constructor
  String(String&& other) noexcept : _data(other._data), _size(other._size) {
    other._data = nullptr;  // Leave the moved-from object in a valid state
    other._size = 0;
  }

  // Move assignment operator
  String& operator=(String&& other) noexcept {
    if (this != &other) {
      delete[] _data;  //  Free existing resource
      _data = other._data;
      _size = other._size;

      // Leave the moved-from object in a valid state
      other._data = nullptr;
      other._size = 0;
    }
    return *this;
  }

  String(const String& other) {
    _size = other._size;
    _data = new char[_size + 1];
    strcpy(_data, other._data);
  }

  // Destructor
  ~String() {
    delete[] _data;
  }

  // Display method
  void display() const {
    if (_data) {
      cout << _data << endl;
    } else {
      cout << "(empty)" << endl;
    }
  }

  size_t size() const {
    return _size;
  }
};

// Without the `explicit` keyword in the constructor an object is instantied implicitly
void take(const String& s) {
  s.display();
}

int main() {
  String s1("Hello World!");
  String s2 = std::move(s1);  // Move constructor
  s2.display();               // -> "Hello World"
  s1.display();               // -> "(empty)" because it was moved from

  String s3;
  s3 = std::move(s2);  // Move assignment operator
  s3.display();        // -> "Hello World"
  s2.display();        // -> "(empty)"

  // take("wtf"); Error: no implicit conversion
  take(String("wtf"));
}
