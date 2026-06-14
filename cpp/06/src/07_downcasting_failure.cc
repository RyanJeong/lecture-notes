#include <iostream>

class Base {
 public:
  virtual ~Base() = default;  // Virtual destructor for RTTI support
};
class Derived : public Base {};
class AnotherDerived : public Base {};

int main() {
  AnotherDerived another_derived;
  Base* p_base = &another_derived;
  // The type of the object pointed to by `p_base` is actually `AnotherDerived`
  Derived* derived_ptr = dynamic_cast<Derived*>(p_base);  // Failed to downcast
  if (!derived_ptr) std::cout << "Failed to downcast to Derived*." << std::endl;

  Base& ref_base = another_derived;
  (void) dynamic_cast<Derived&>(ref_base);
  // -> Failed to downcast to Derived&; throws std::bad_cast exception.
  return 0;
}
