// Example demonstrating key aspects of std::vector in C++14
#include <iostream>
#include <vector>  // for std::vector

int main() {
  std::vector<int> vec = {1, 2, 3};  // 1. Initialization

  // 2. Memory optimization (critical)
  vec.reserve(10);  // Prevent frequent reallocations
  std::cout << "Capacity: " << vec.capacity() << std::endl;  // 10

  // 3. Insertion operations
  vec.push_back(10);                // Fast: O(1) amortized
  vec.insert(vec.begin() + 1, 99);  // Slow: O(n), shifts elements

  // 4. Access
  std::cout << "vec[2]: " << vec[2] << std::endl;
  std::cout << "vec.at(2): " << vec.at(2) << std::endl;  // Bounds checking

  // 5. Range-based for loop (shorten for loop syntax using iterators)
  for (int n : vec) std::cout << n << " ";
  std::cout << std::endl;
  return 0;
}
