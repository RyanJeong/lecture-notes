#include <iostream>

#include "circle.hpp"
#include "ellipse.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

int main() {
  Square sq(5);
  sq.Print();
  std::cout << "Area: " << sq.GetArea() << std::endl;
  std::cout << "Perimeter: " << sq.GetPerimeter() << std::endl << std::endl;

  Rectangle rect(5, 4);
  rect.Print();
  std::cout << "Area: " << rect.GetArea() << std::endl;
  std::cout << "Perimeter: " << rect.GetPerimeter() << std::endl << std::endl;

  Triangle tri(3, 4, 5);
  tri.Print();
  std::cout << "Area: " << tri.GetArea() << std::endl;
  std::cout << "Perimeter: " << tri.GetPerimeter() << std::endl << std::endl;

  Circle circ(5);
  circ.Print();
  std::cout << "Area: " << circ.GetArea() << std::endl;
  std::cout << "Perimeter: " << circ.GetPerimeter() << std::endl << std::endl;

  Ellipse elps(5, 4);
  elps.Print();
  std::cout << "Area: " << elps.GetArea() << std::endl;
  std::cout << "Perimeter: " << elps.GetPerimeter() << std::endl << std::endl;
  return 0;
}
