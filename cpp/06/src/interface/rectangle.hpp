#pragma once

#include "shape.hpp"

class Rectangle : public Shape {
  bool IsValid() const override;

  double length_;
  double width_;

 public:
  Rectangle(double length, double width);
  ~Rectangle() = default;

  void Print() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
};
