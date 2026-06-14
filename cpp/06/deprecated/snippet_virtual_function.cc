#ifdef CPP_06_SNIPPET_VIRTUAL_FUNCTION_CC
#include <iostream>

class Animal {
 public:
  virtual void Move() const { std::cout << "Animal moves" << std::endl; }
};

class Dog : public Animal {
 public:
  virtual void Move(int y, int x) const {  // New virtual function
    // Not an override; different signature
    // If you write 'override' here, it will cause a compilation error.
    std::cout << "Dog moves to (" << y << ", " << x << ")" << std::endl;
  }
  void Move() const override {  // Proper override
    std::cout << "Dog moves" << std::endl;
  }
};
#endif  // CPP_06_SNIPPET_VIRTUAL_FUNCTION_CC
