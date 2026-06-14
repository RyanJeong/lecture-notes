#include "name.hpp"

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

Name::Name(const std::string& fst, const std::string& i, const std::string& lst)
    : first_(fst), init_(i), last_(lst) {
  assert(init_.size() == 1);
  first_[0] = std::toupper(first_[0]);
  init_[0] = std::toupper(init_[0]);
  last_[0] = std::toupper(last_[0]);
}

void Name::Print() const {
  std::cout << "Employee name: " << first_ << " " << init_ << ". ";
  std::cout << last_ << std::endl;
}
