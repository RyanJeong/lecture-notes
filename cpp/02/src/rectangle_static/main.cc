#include <iostream>

#include "rectangle.hpp"

int main() {
  Rectangle rect1(3.0, 4.2);
  std::cout << "Rectangle 1: ";
  rect1.Print();
  std::cout << "Area: " << rect1.Area() << std::endl;
  std::cout << "Perimeter: " << rect1.Perimeter() << std::endl << std::endl;
  std::cout << "Count of objects: " << rect1.get_count() << std::endl;
  {
    Rectangle rect2(3.2, 1.2), rect3(rect1);
    std::cout << "Count of objects: " << rect2.get_count() << std::endl;
  }
  std::cout << "Count of objects: " << Rectangle::get_count() << std::endl;
  return 0;
}
