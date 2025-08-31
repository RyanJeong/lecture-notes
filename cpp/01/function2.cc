#include <iostream>

// Modifies the original argument (call by reference).
// References allow direct access to the original variable without needing
// additional operators like '*' (dereferencing).
void ModifyByReference(int& ref) {
  ref = 100;
  std::cout << "&ref: " << &ref << std::endl;
}

int main() {
  int num = 10;

  std::cout << "Before ModifyByReference: num = " << num << std::endl;
  std::cout << "&num: " << &num << std::endl;
  ModifyByReference(num);
  std::cout << "After ModifyByReference: num = " << num << std::endl;
  return 0;
}