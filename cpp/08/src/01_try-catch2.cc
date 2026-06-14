#include <iostream>

int Quotient(int numer, int denom) {
  if (!denom) throw 0;
  return numer / denom;
}

int main() {
  int numer, denom;
  for (int i = 0; i < 5; ++i) {
    std::cout << "Enter an integer: ";
    std::cin >> numer;
    std::cout << "Enter another integer: ";
    std::cin >> denom;

    try {
      std::cout << "Result: " << Quotient(numer, denom) << std::endl;
    } catch (int e) {
      std::cerr << "Division by zero cannot be performed." << std::endl;
    }
  }
  return 0;
}
