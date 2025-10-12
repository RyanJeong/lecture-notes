#pragma once

class PrfType {
 protected:
  double salary_;

 public:
  virtual void PrintSalary() const = 0;
};
