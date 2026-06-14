#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>

#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Base {
 public:
  virtual void Print() const { std::cout << "Base::Print" << std::endl; }
};

class Derived : public Base {
 public:
  void Print() const override { std::cout << "Derived::Print" << std::endl; }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
  Base* ptr = new Base();
  ptr->Print();
  delete ptr;
  ptr = new Derived();
  ptr->Print();
  delete ptr;
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
