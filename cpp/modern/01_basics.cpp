#include <charconv>
#include <format>
#include <iostream>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std;

/* Static assertions */
void assert_test() {
  static_assert(sizeof(int) == 4, "Requires 4-byte integers");
  cout << "No issue with the assertion" << endl;
}

/* Lambdas (closures) */
void lambda_test() {
  int x = 5;
  auto sum = [x](int y) { return x + y; };
  cout << sum(10) << endl;
}

/* Parsing numbers #charconv */
void convert_test() {
  const char* str = "12345";
  int num = 0;
  from_chars(str, str + 5, num);
  cout << "Converted number: " << num << endl;
}

/* Formatting string #format (for now missing on my machine)*/
/* void format_test() {
  const char* name = "Jordi";
  int age = 25;
  string msg = format("name={} age=age", name, age);
  cout << msg << endl;
} */

/* Optional values #optional */
optional<int> divide(int a, int b) {
  if (b == 0) {
    return nullopt;
  } else {
    return a / b;
  }
}
void divide_test() {
  optional<int> result = divide(10, 2);
  if (result) {  // Checks for inner value, could also use `result.has_value()`
    cout << "Result: " << *result << endl;
  } else {
    cout << "Divison by zero" << endl;
  }
}

void string_view_test() {
  string str = "Hello World";
  string_view view(str.c_str(), 5);
  cout << view << endl;
}

/* Slices #span */
void slice_test() {
  array<int, 5> arr = {1, 2, 3, 4, 5};
  span<int> slice(arr.begin() + 1, 3);
  for (int n : slice) cout << n << ' ';
  cout << '\n';
}

/* Exceptions #stdexcept */
void might_throw(bool should_throw) {
  if (should_throw) {
    throw runtime_error("An error ocurred");
  }
}
void exception_test() {
  try {
    might_throw(true);
  } catch (const std::exception& e) {
    cout << "Caught exception: " << e.what() << endl;
  }
}

/* Templates (generics, static dispatch, polymorphism) */
template <typename T>
T add(T a, T b) {
  return a + b;
}
void template_test() {
  int x = add(2, 3);         // add<int>
  double y = add(2.5, 3.5);  // add<double>
}

int main() {
  assert_test();
  lambda_test();
  convert_test();
  divide_test();
  // format_test();
  string_view_test();
  slice_test();
  exception_test();
  template_test();
}
