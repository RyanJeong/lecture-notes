#include <iostream>

// Function declarations
void NonTemplateFunction();

template <typename T>
void TemplateFunction(T value);

// specialization for int
template <>
void TemplateFunction<int>(int value);

template <typename T>
class MyClass {
  T value_;  // Internal value of the class

 public:
  explicit MyClass(T value) : value_(value) {}

  // Declare friend functions
  friend void NonTemplateFunction();
  template <typename U>
  friend void TemplateFunction(U value);
  friend void TemplateFunction<int>(int value);
};

void NonTemplateFunction() {
  MyClass<int> obj(42);
  std::cout << "Non-template friend function called! Value: " << obj.value_
            << std::endl;
}

template <typename T>
void TemplateFunction(T value) {
  MyClass<T> obj(value);
  std::cout << "Template friend function called with value: " << obj.value_
            << std::endl;
}

template <>
void TemplateFunction<int>(int value) {
  MyClass<int> obj(value);
  std::cout << "Specialized template friend function for int called! Value: "
            << obj.value_ << std::endl;
}

int main() {
  NonTemplateFunction();
  TemplateFunction<double>(3.14);
  TemplateFunction<int>(100);
  return 0;
}
