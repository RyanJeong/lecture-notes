#include "rectangle.hpp"

#include <cassert>
#include <iostream>

Rectangle::Rectangle(double length, double width)
    : length_(length), width_(width) {
  assert(IsValid());
}

void Rectangle::Print() const {
  std::cout << "Rectangle of " << length_ << " X " << width_ << std::endl;
}

double Rectangle::GetArea() const { return length_ * width_; }

double Rectangle::GetPerimeter() const { return 2 * (length_ + width_); }

bool Rectangle::IsValid() const { return length_ > 0.0 && width_ > 0.0; }
