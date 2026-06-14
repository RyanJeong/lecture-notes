#pragma once

class Shape {
  virtual bool IsValid() const = 0;

 public:
  virtual void Print() const = 0;
  virtual double GetArea() const = 0;
  virtual double GetPerimeter() const = 0;
};
