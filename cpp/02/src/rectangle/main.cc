#include <iostream>

#include "rectangle.hpp"

int main() {
  Rectangle rect1(3.0, 4.2), rect2(rect1);

  std::cout << "Rectangle 1: ";
  rect1.Print();
  std::cout << "Area: " << rect1.Area() << std::endl;
  std::cout << "Perimeter: " << rect1.Perimeter() << std::endl << std::endl;

  std::cout << "Rectangle 2: ";
  rect2.Print();
  std::cout << "Area: " << rect2.Area() << std::endl;
  std::cout << "Perimeter: " << rect2.Perimeter() << std::endl << std::endl;
  return 0;
}
