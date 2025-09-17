#pragma once

class Rectangle {
 public:
  Rectangle(double length, double height);
  Rectangle(const Rectangle& rect);
  ~Rectangle() = default;
  // This class defines a parameter constructor and implicitly ignores the
  // default constructor as below:
  // Rectangle() = delete;  // Because a parameter constructor is defined

  void Print() const;
  double Area() const;
  double Perimeter() const;

 private:
  double length_;
  double height_;
};
