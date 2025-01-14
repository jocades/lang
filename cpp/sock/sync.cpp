#include <array>
#include <iostream>
#include <string>

using namespace std;

void give(array<int, 2>& a) {}

int main() {
  array<char, 2> a = {};
  auto [first, second] = a;
  cout << first << ' ' << second << '\n';

  a.fill('a');
  char b[4] = "abc";
  cout << b << '\n';
}
