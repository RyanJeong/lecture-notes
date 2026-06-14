#include <iostream>

#include "fraction.hpp"

int main() {
  std::cout << "=== Fraction Operator Overloading Demo ===" << std::endl;

  // Construction and basic operations
  std::cout << "\n--- Construction ---" << std::endl;
  Fraction f1(3, 4);
  std::cout << "f1(3, 4) = " << f1 << std::endl;

  Fraction f2(1, 2);
  std::cout << "f2(1, 2) = " << f2 << std::endl;

  Fraction f3(0.75);  // Implicit conversion from double
  std::cout << "f3(0.75) = " << f3 << std::endl;

  // Unary operators
  std::cout << "\n--- Unary Operators ---" << std::endl;
  std::cout << "+f1 = " << +f1 << std::endl;
  std::cout << "-f1 = " << -f1 << std::endl;

  // Binary arithmetic operators
  std::cout << "\n--- Binary Arithmetic Operators ---" << std::endl;
  std::cout << "f1 + f2 = " << (f1 + f2) << std::endl;
  std::cout << "f1 - f2 = " << (f1 - f2) << std::endl;
  std::cout << "f1 * f2 = " << (f1 * f2) << std::endl;
  std::cout << "f1 / f2 = " << (f1 / f2) << std::endl;

  // Compound assignment operators
  std::cout << "\n--- Compound Assignment Operators ---" << std::endl;
  Fraction f4(1, 3);
  Fraction f5(1, 6);
  std::cout << "f4(1, 3) = " << f4 << ", f5(1, 6) = " << f5 << std::endl;

  f4 += f5;
  std::cout << "After f4 += f5: f4 = " << f4 << std::endl;

  f4 -= Fraction(1, 2);
  std::cout << "After f4 -= 1/2: f4 = " << f4 << std::endl;

  f4 *= Fraction(2, 1);
  std::cout << "After f4 *= 2: f4 = " << f4 << std::endl;

  f4 /= Fraction(2, 1);
  std::cout << "After f4 /= 2: f4 = " << f4 << std::endl;

  // Increment and decrement operators
  std::cout << "\n--- Increment and Decrement Operators ---" << std::endl;
  Fraction f6(1, 2);
  std::cout << "f6(1, 2) = " << f6 << std::endl;
  std::cout << "++f6 = " << ++f6 << " (pre-increment)" << std::endl;
  std::cout << "f6 = " << f6 << std::endl;

  Fraction f7(1, 2);
  std::cout << "f7(1, 2) = " << f7 << std::endl;
  std::cout << "f7++ = " << f7++ << " (post-increment)" << std::endl;
  std::cout << "f7 = " << f7 << std::endl;

  Fraction f8(3, 2);
  std::cout << "f8(3, 2) = " << f8 << std::endl;
  std::cout << "--f8 = " << --f8 << " (pre-decrement)" << std::endl;
  std::cout << "f8 = " << f8 << std::endl;

  Fraction f9(3, 2);
  std::cout << "f9(3, 2) = " << f9 << std::endl;
  std::cout << "f9-- = " << f9-- << " (post-decrement)" << std::endl;
  std::cout << "f9 = " << f9 << std::endl;

  // Comparison operators
  std::cout << "\n--- Comparison Operators ---" << std::endl;
  Fraction f10(2, 4);
  Fraction f11(1, 2);
  Fraction f12(3, 4);
  std::cout << "f10(2, 4) = " << f10 << ", f11(1, 2) = " << f11
            << ", f12(3, 4) = " << f12 << std::endl;
  std::cout << "f10 == f11: " << (f10 == f11 ? "true" : "false") << std::endl;
  std::cout << "f10 != f12: " << (f10 != f12 ? "true" : "false") << std::endl;
  std::cout << "f10 < f12: " << (f10 < f12 ? "true" : "false") << std::endl;
  std::cout << "f10 <= f11: " << (f10 <= f11 ? "true" : "false") << std::endl;
  std::cout << "f12 > f10: " << (f12 > f10 ? "true" : "false") << std::endl;
  std::cout << "f10 >= f11: " << (f10 >= f11 ? "true" : "false") << std::endl;

  // Type conversion
  std::cout << "\n--- Type Conversion ---" << std::endl;
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Fraction f13(3, 4);
  double d = static_cast<double>(f13);
  std::cout << "f13(3, 4) = " << f13 << ", as double = " << d << std::endl;
  // The following expression implicitly calls the conversion operator int()
  std::cout << "1 + f13 = " << (1 + f13) << std::endl;
  // The following expression explicitly calls the conversion operator double()
  std::cout << "1 + f13 = " << (1 + static_cast<double>(f13)) << std::endl;
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  // Assignment operator
  std::cout << "\n--- Assignment Operator ---" << std::endl;
  Fraction f14(5, 6);
  Fraction f15(1, 3);
  std::cout << "f14(5, 6) = " << f14 << ", f15(1, 3) = " << f15 << std::endl;
  f14 = f15;
  std::cout << "After f14 = f15: f14 = " << f14 << std::endl;

  return 0;
}
