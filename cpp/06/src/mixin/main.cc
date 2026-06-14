#include <iostream>

#include "professor.hpp"
#include "student.hpp"
#include "ta.hpp"

int main() {
  Person person("John");
  person.Print();

  Student student("Linda", 3.9);
  student.Print();

  Professor professor("George", 89000);
  professor.Print();

  TA ta("Lucien", 3.8, 23000);
  ta.Print();
  return 0;
}
