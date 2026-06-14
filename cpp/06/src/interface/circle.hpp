#pragma once

#include "shape.hpp"

class Circle : public Shape {
  bool IsValid() const override;

  double radius_;

 public:
  explicit Circle(double radius);
  ~Circle() = default;

  void Print() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
};
