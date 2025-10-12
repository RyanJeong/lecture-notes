#include "triangle.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

Triangle::Triangle(double s1, double s2, double s3)
    : side1_(s1), side2_(s2), side3_(s3) {
  assert(IsValid());
}

void Triangle::Print() const {
  std::cout << "Triangle of: " << side1_ << " X " << side2_ << " X " << side3_
            << std::endl;
}

double Triangle::GetArea() const {
  double s = (side1_ + side2_ + side3_) / 2;
  return (std::sqrt(s * (s - side1_) * (s - side2_) * (s - side3_)));
}

double Triangle::GetPerimeter() const { return side1_ + side2_ + side3_; }

bool Triangle::IsValid() const {
  bool fact1 = side1_ + side2_ > side3_;
  bool fact2 = side1_ + side3_ > side2_;
  bool fact3 = side2_ + side3_ > side1_;
  return fact1 && fact2 && fact3;
}
