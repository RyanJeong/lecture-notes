#include <iostream>

int main() {
  // Single integer allocation
  int* p_i = new int;      // Uninitialized
  int* p_j = new int(42);  // Initialized with 42

  *p_i = 10;
  std::cout << "p_i: " << *p_i << std::endl;  // Output: 10
  std::cout << "p_j: " << *p_j << std::endl;  // Output: 42

  // Memory deallocation
  delete p_i;
  delete p_j;
  return 0;
}