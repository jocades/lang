#include <iostream>
#include <vector>
using std::vector, std::cout;

void take(vector<int>&& nums) {
  for (int& n : nums) n *= 2;
}

int main() {
  vector<int> nums{1, 2, 3};
  take(std::move(nums));
  nums.clear();
  for (auto n : nums) cout << n << '\n';
}
