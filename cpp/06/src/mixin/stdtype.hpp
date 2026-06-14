#pragma once

class StdType {
 protected:
  double gpa_;

 public:
  virtual ~StdType() = default;

  virtual void PrintGpa() const = 0;
};
