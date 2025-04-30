#include <algorithm>
#include <iostream>

using std::cout;

template <typename T>
class Vec {
 private:
  T* _ptr;
  size_t _cap;
  size_t _len;

  void grow() {
    size_t ncap = _cap < 8 ? 8 : _cap * 2;
    T* nptr = new T[ncap];
    std::copy(_ptr, _ptr + _len, nptr);
    delete[] _ptr;
    _cap = ncap;
    _ptr = nptr;
  }

 public:
  Vec() noexcept : _ptr(nullptr), _cap(0), _len(0) {
    cout << "default constructor\n";
  }

  // with capacity;
  explicit Vec(size_t cap) : _ptr(new T[cap]), _cap(cap), _len(0) {
    cout << "with capacity constructor\n";
  }

  Vec(const Vec& other) : _ptr(new T[other._cap]), _cap(other._cap), _len(other._len) {
    cout << "copy constructor\n";
    std::copy(other._ptr, other._ptr + other._len, _ptr);
  }

  Vec(Vec&& other) noexcept : _ptr(other._ptr), _cap(other._cap), _len(other._len) {
    cout << "move constructor\n";
    other._ptr = nullptr;
    other._cap = other._len = 0;
  }

  Vec& operator=(const Vec& other) {
    cout << "copy assignment\n";
    if (this != &other) {
      Vec tmp(other);  // Copy and swap idiom
      std::swap(*this, tmp);
      // delete[] _ptr;
      // _ptr = new T[other._cap];
      // _cap = other._cap;
      // _len = other._len;
      // std::copy(other._ptr, other._ptr + other._cap, _ptr);
    }
    return *this;
  }

  Vec& operator=(Vec&& other) noexcept {
    cout << "move assignment\n";
    if (this != &other) {
      delete[] _ptr;
      _ptr = other._ptr;
      _cap = other._cap;
      _len = other._len;
      other._ptr = nullptr;
      other._cap = other._len = 0;
    }
    return *this;
  }

  ~Vec() {
    delete[] _ptr;
  }

  /**
   * Accessors
   */
  size_t cap() const noexcept {
    return _cap;
  }
  size_t len() const noexcept {
    return _len;
  }
  bool is_empty() const noexcept {
    return _len == 0;
  }

  /**
   * Element access
   */
  T& operator[](size_t index) {
    return _ptr[index];
  }
  const T& operator[](size_t index) const {
    return _ptr[index];
  }

  /**
   * Modifiers
   */
  void push(const T& v) {
    if (_cap == _len) grow();
    _ptr[_len++] = v;
  }

  friend std::ostream& operator<<(std::ostream& stream, const Vec& v) {
    T* i = v._ptr;
    T* e = v._ptr + v._len;
    stream << '[';
    for (; i < e; i++) {
      stream << *i;
      if (i != e - 1) stream << ", ";
    }
    stream << ']';
    return stream;
  }
};

int main() {
  Vec<char> v1;
  for (int i = 0; i < 5; i++) v1.push(97 + i);
  cout << v1 << '\n';
  cout << v1[3] << '\n';

  auto v2 = std::move(v1);
  assert(v1.is_empty() && v1.cap() == 0);
  assert(v2.len() == 5);
}
