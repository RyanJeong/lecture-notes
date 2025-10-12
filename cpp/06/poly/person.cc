#include "person.hpp"

#include <iostream>
#include <string>

Person::Person(const std::string& nm) : name_(nm) {
  std::cout << "Person's ctor" << std::endl;
}

Person::~Person() { std::cout << "Person's dtor" << std::endl; }

void Person::print() const { std::cout << "Name: " << name_ << std::endl; }
