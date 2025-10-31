#include <iostream>

int main() {
  int numer, denom;
  for (int i = 0; i < 5; ++i) {
    std::cout << "Enter an integer: ";
    std::cin >> numer;
    std::cout << "Enter another integer: ";
    std::cin >> denom;

    try {
      if (!denom) throw 0;

      std::cout << "The result of division is: "
                << static_cast<double>(numer) / denom << std::endl;
    } catch (int x) {  // side-effect (int x = 0)
      std::cerr << "No division by zero." << std::endl;
    }
  }
  return 0;
}
