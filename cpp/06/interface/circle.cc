#include "circle.hpp"

#include <cassert>
#include <iostream>

Circle::Circle(double r) : radius_(r) { assert(IsValid()); }

void Circle::Print() const {
  std::cout << "Circle of radius: " << radius_ << std::endl;
}

double Circle::GetArea() const { return 3.14 * radius_ * radius_; }

double Circle::GetPerimeter() const { return 2 * 3.14 * radius_; }

bool Circle::IsValid() const { return radius_ > 0.0; }
