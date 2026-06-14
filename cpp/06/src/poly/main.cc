#include <iostream>

#include "student.hpp"

int main() {
  Person* ptr = new Person("Lucie");
  std::cout << "Person Information";
  ptr->Print();
  delete ptr;

  std::cout << std::endl;

  ptr = new Student("John", 3.9);
  std::cout << "Student Information";
  ptr->Print();
  delete ptr;
  return 0;
}
