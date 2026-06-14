#include <iostream>

int Quotient(int numer, int denom) {
  try {
    if (!denom) throw 0;
    return numer / denom;
  } catch (int e) {
    // If you're doing resource management, you can clean up here
    std::cout << std::endl;
    std::cerr << "[Quotient] Error detected in Quotient()" << std::endl;
    std::cerr << "[Quotient] Logging: numer=" << numer << ", denom=" << denom
              << std::endl;
    throw;  // Re-throw the exception to be caught by the outer try-catch
  }
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
