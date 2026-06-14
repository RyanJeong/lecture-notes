#pragma once

#include "shape.hpp"

class Ellipse : public Shape {
  bool IsValid() const override;

  double radius1_;
  double radius2_;

 public:
  Ellipse(double r1, double r2);
  ~Ellipse() = default;

  void Print() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
};
