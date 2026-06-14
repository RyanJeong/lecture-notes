#pragma once

class PrfType {
 protected:
  double salary_;

 public:
  virtual ~PrfType() = default;

  virtual void PrintSalary() const = 0;
};
