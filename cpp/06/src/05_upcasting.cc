class Base {
 public:
  virtual ~Base() = default;  // Virtual destructor for RTTI support
};
class Derived : public Base {};

int main() {
  // Upcasting (Derived -> Base): Implicit upcasting, it's always safe and no
  //                              cast operator needed
  Derived derived;
  Base* p_base = &derived;  // Polymorphism is the use of upcasting
  (void) p_base;

  return 0;
}
