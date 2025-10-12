class Base {
 public:
  virtual ~Base() = default;  // Virtual destructor for RTTI support
};
class Derived : public Base {};

int main() {
  Derived derived;

  Base* p_base = &derived;
  Derived* derived_ptr = dynamic_cast<Derived*>(p_base);
  // -> Succeeded in downcasting to Derived*

  Base& ref_base = derived;
  Derived& ref_derived = dynamic_cast<Derived&>(ref_base);
  // -> Succeeded in downcasting to Derived&

  return 0;
}
