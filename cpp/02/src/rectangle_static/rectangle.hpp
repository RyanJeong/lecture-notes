#pragma once

class Rectangle {
 public:
  Rectangle(double length, double height);
  Rectangle(const Rectangle& rect);
  ~Rectangle();

  static int get_count();  // getter
  void Print() const;
  double Area() const;
  double Perimeter() const;

 private:
  static int count_;
  double length_;
  double height_;
};