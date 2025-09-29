#ifdef CPP_06_SNIPPET_VIRTUAL_FUNCTION_CC
#include <iostream>

class Animal {
 public:
  virtual void Move() const { std::cout << "Animal moves" << std::endl; }
};

class Dog : public Animal {
 public:
  // This is not a proper override because the signature is different.
  // Therefore, the 'virtual' keyword is used to declare a new virtual function,
  // not to indicate an override. If you use the 'override' keyword here, the
  // compiler will generate an error.
  virtual void Move(int y, int x) const {
    std::cout << "Dog moves to (" << y << ", " << x << ")" << std::endl;
  }
};
#endif  // CPP_06_SNIPPET_VIRTUAL_FUNCTION_CC