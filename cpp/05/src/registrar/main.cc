#include "registrar.hpp"

int main() {
  Registrar registrar;

  Student student1("John");
  Student student2("Mary");
  Course course1("CIS101", 4);
  Course course2("CIS102", 3);
  Course course3("CIS103", 3);

  registrar.Enroll(student1, course1);
  registrar.Enroll(student1, course2);
  registrar.Enroll(student2, course1);
  registrar.Enroll(student2, course3);
  student1.Print();
  student2.Print();
  course1.Print();
  course2.Print();
  course3.Print();
  return 0;
}
