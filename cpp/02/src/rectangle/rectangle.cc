#include "rectangle.hpp"

#include <cassert>
#include <iostream>

Rectangle::Rectangle(double len, double hgt) : length_(len), height_(hgt) {
  if (length_ <= 0.0 || height_ <= 0.0) {
    std::cout << "No rectangle can be made!" << std::endl;
    assert(false);
  }
}

Rectangle::Rectangle(const Rectangle& rect)
    : length_(rect.length_), height_(rect.height_) {}

void Rectangle::Print() const {
  std::cout << "A rectangle of " << length_ << " by " << height_ << std::endl;
}

double Rectangle::Area() const { return length_ * height_; }

double Rectangle::Perimeter() const { return 2 * (length_ + height_); }
