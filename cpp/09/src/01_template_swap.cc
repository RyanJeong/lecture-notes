#include <iostream>

template <typename T>
void Exchange(T* op1, T* op2) {
  T temp = *op1;
  *op1 = *op2;
  *op2 = temp;
}

int main() {
  int i1 = 5;
  int i2 = 70;
  Exchange(&i1, &i2);  // Swapping two int types
  std::cout << "After swapping 5 and 70: " << i1 << " " << i2 << std::endl;

  double d1 = 1.2;
  double d2 = 3.4;
  Exchange(&d1, &d2);  // Swapping two double types
  std::cout << "After swapping 1.2 and 3.4: " << d1 << " " << d2 << std::endl;
  return 0;
}
