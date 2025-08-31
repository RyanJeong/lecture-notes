#include <iostream>

// Modifies a copy of the argument (call by value).
void ModifyByValue(int value) { value = 100; }

// Modifies the original argument (call by address).
void ModifyByAddress(int* ptr) { *ptr = 100; }

int main() {
  int num = 10;
  std::cout << "Before ModifyByValue: num = " << num << std::endl;
  ModifyByValue(num);
  std::cout << "After ModifyByValue: num = " << num << std::endl;

  std::cout << "Before ModifyByAddress: num = " << num << std::endl;
  ModifyByAddress(&num);
  std::cout << "After ModifyByAddress: num = " << num << std::endl;
  return 0;
}
