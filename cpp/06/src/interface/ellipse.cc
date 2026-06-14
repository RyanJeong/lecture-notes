#include "ellipse.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

Ellipse::Ellipse(double r1, double r2) : radius1_(r1), radius2_(r2) {
  assert(IsValid());
}

void Ellipse::Print() const {
  std::cout << "Ellipse: " << radius1_ << " x " << radius2_ << std::endl;
}

double Ellipse::GetArea() const { return 3.14 * radius1_ * radius2_; }

double Ellipse::GetPerimeter() const {
  double temp = (radius1_ * radius1_ + radius2_ * radius2_) / 2.0;
  return 2 * 3.14 * std::sqrt(temp);
}

bool Ellipse::IsValid() const { return radius1_ > 0.0 && radius2_ > 0.0; }
