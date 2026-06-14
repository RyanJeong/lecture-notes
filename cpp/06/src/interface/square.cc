#include "square.hpp"

#include <cassert>
#include <iostream>

Square::Square(double s) : side_(s) { assert(IsValid()); }

void Square::Print() const {
  std::cout << "Square of size " << side_ << std::endl;
}

double Square::GetArea() const { return side_ * side_; }

double Square::GetPerimeter() const { return 4 * side_; }

bool Square::IsValid() const { return side_ > 0.0; }
