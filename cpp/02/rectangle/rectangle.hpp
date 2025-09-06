#pragma once

class Rectangle {
 public:
  Rectangle(double length, double height);
  Rectangle(const Rectangle& rect);
  ~Rectangle() = default;

  void Print() const;
  double Area() const;
  double Perimeter() const;

 private:
  double length_;
  double height_;
};
