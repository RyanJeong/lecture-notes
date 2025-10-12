#pragma once

#include "shape.hpp"

class Triangle : public Shape {
  bool IsValid() const override;

  double side1_;
  double side2_;
  double side3_;

 public:
  Triangle(double side1, double side2, double side3);
  ~Triangle() = default;

  void Print() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
};
