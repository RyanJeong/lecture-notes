#include "ta.hpp"

int main() {
  Person person("John");
  person.Print();

  Student student("Anne", 3.9);
  student.Print();

  Professor professor("Lucie", 78000);
  professor.Print();

  TA ta("George", 3.2, 20000);
  ta.Print();

  return 0;
}
