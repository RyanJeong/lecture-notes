#include "person.hpp"

#include <iostream>
#include <string>

Person::Person(const std::string& nm) : name_(nm) {}

void Person::PrintName() const { std::cout << "Name: " << name_ << std::endl; }

void Person::Print() const {
  PrintName();
  std::cout << std::endl;
}
