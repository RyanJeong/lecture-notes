#include "person.hpp"

#include <iostream>
#include <string>

Person::Person(const std::string& nm) : name_(nm) {}

void Person::Print() const {
  std::cout << "Person" << std::endl;
  std::cout << "Name: " << name_ << std::endl << std::endl;
}
