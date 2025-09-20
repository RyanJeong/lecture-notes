#include "rectangle.hpp"

#include <cassert>
#include <iostream>

int Rectangle::count_ = 0;

Rectangle::Rectangle(double len, double hgt) : length_(len), height_(hgt) {
  if (length_ <= 0.0 || height_ <= 0.0) {
    std::cout << "No rectangle can be made!" << std::endl;
    assert(false);
  }
  ++count_;
}

Rectangle::Rectangle(const Rectangle& rect)
    : length_(rect.length_), height_(rect.height_) {
  ++count_;
}

Rectangle::~Rectangle() { --count_; }

int Rectangle::get_count() { return count_; }

// All member functions have the `this` pointer as an implicit parameter.
// `this` pointer points to the object for which the member function is called.
void Rectangle::Print() const {
  std::cout << "A rectangle of " << this->length_ << " by " << this->height_
            << std::endl;
}

double Rectangle::Area() const { return this->length_ * this->height_; }

double Rectangle::Perimeter() const {
  return 2 * (this->length_ + this->height_);
}
