#pragma once

class Date {
  int month_;
  int day_;
  int year_;

 public:
  Date(int month, int day, int year);

  void Print() const;
};
