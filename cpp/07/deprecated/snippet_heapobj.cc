#include "fraction/fraction.hpp"

void Foo() {
  // Some operations that may throw exceptions
  throw std::runtime_error("An error occurred in Foo");
}

void UtilizeHeapObject() {
  Fraction* ptr_fr = new Fraction(3, 4);

  Foo();  // Some errors may occur here, e.g., exceptions thrown, and the object
          // pointed to by `ptr_fr` may not be properly deleted.
  delete ptr_fr;
}
