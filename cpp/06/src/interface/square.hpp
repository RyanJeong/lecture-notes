#pragma once

#include "shape.hpp"

class Square : public Shape {
  bool IsValid() const override;

  double side_;

 public:
  explicit Square(double side);
  ~Square() = default;

  void Print() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
};
