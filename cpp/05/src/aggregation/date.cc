#include "date.hpp"

#include <cassert>
#include <iostream>

Date::Date(int m, int d, int y) : month_(m), day_(d), year_(y) {
  static int day_in_month[13] = {0,  // 1-based
                                 31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};
  assert(month_ >= 1 && month_ <= 12);
  assert(day_ >= 1 && day_ <= day_in_month[month_]);
  assert(year_ >= 1900 && year_ <= 2099);
}

void Date::Print() const {
  std::cout << month_ << "/" << day_ << "/" << year_ << std::endl;
}
