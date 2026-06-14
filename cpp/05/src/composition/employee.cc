#include "employee.hpp"

#include <iostream>
#include <string>

Employee::Employee(const std::string& fst, const std::string& i,
                   const std::string& lst, double salary)
    : name_(fst, i, lst), salary_(salary) {
  assert(salary_ > 0.0 && salary_ < 100000.0);
}

void Employee::Print() const {
  name_.Print();
  std::cout << "Salary: " << salary_ << std::endl << std::endl;
}
