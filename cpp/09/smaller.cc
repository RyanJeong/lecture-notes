#include <iostream>

template <typename T>
T Smaller(const T& op1, const T& op2) {
  return op1 < op2 ? op1 : op2;
}

// Template function with three parameters through overloading. Note that the
// second function is defined in terms of the first one, which is why it is
// shorter.
template <typename T>
T Smaller(const T& op1, const T& op2, const T& op3) {
  return Smaller(Smaller(op1, op2), op3);
}

int main() {
  // Calling the overloaded version with three integers
  std::cout << "Smaller of 17, 12, and 27 is ";
  std::cout << Smaller(17, 12, 27) << std::endl;
  return 0;
}

#include <cstring>  // for std::strcmp

// const (T)&
// -> const (const char*)& : make sure the pointer itself is also const
// -> const char* const&
template <>
const char* Smaller(const char* const& op1, const char* const& op2) {
  return std::strcmp(op1, op2) < 0 ? op1 : op2;
}
