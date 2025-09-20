#include <iomanip>  // for std::setprecision
#include <iostream>

int main() {
  int num = 255;
  float pi = 3.14159265f;
  bool flag = true;

  // Boolean output format (default: std::noboolalpha, 0/1) - persists
  std::cout << std::boolalpha << flag << " ";  // "true"
  std::cout << flag << std::endl;              // "true" (persists)
  // Number base format (default: decimal) - persists
  std::cout << std::hex << std::showbase << num << " ";    // "0xff"
  std::cout << num << std::endl;                           // "0xff" (persists)
  std::cout << std::oct << std::noshowbase << num << " ";  // "377"
  std::cout << num << std::endl;                           // "377" (persists)
  // Float precision - persists
  std::cout << std::fixed << std::setprecision(2) << pi << " ";  // "3.14"
  std::cout << pi << std::endl;  // "3.14" (persists)
  return 0;
}