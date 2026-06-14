#include "employee.hpp"

int main() {
  // Here's the instantiation part. Notice that the lifetime of the composee is
  // DEPENDENT of the lifetime of the composer.
  Employee employee1("Mary", "B", "White", 22120.00);
  Employee employee2("William", "S", "Black", 46700.00);
  Employee employee3("Ryan", "A", "Brown", 12500.00);

  employee1.Print();
  employee2.Print();
  employee3.Print();
  return 0;
}
