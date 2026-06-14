#pragma once

void FreeFunction();

template <typename T>
void TemplateFunction(T value);

// specialization for int
template <>
void TemplateFunction<int>(int value);

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
template <typename T>
class MyClass {
  T value_;  // Internal value of the class

 public:
  explicit MyClass(T value) : value_(value) {}

  // Declare FreeFunction as a friend
  friend void FreeFunction();

  // Declare TemplateFunction as a friend
  template <typename U>
  friend void TemplateFunction(U value);

  // Declare specialization as a friend
  friend void TemplateFunction<int>(int value);
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void FreeFunction() {
  MyClass<double> obj(3.14);
  obj.value_ += 1.0;  // Accessing private member value_
}

template <typename T>
void TemplateFunction(T value) {
  MyClass<T> obj(value);
  obj.value_ += value;  // Accessing private member value_
}

// specialization for int
template <>
void TemplateFunction<int>(int value) {
  MyClass<int> obj(value);
  obj.value_ += 10;  // Accessing private member value_
}
