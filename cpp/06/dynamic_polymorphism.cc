#include <iostream>

class Base {
 public:
  virtual void Print() const { std::cout << "Base::Print" << std::endl; }
};

class Derived : public Base {
 public:
  void Print() const override { std::cout << "Derived::Print" << std::endl; }
};

int main() {
  Base* ptr = new Base();
  ptr->Print();
  delete ptr;
  ptr = new Derived();
  ptr->Print();
  delete ptr;
  return 0;
}
