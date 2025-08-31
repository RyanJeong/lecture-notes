#include <iostream>  // C++ standard input/output stream header
                     // Unlike C, C++ headers do not use file extensions
int main() {
  std::cout << "Hello, world"  // std::cout: standard output stream object
            << std::endl;      // std::endl: manipulator for newline + flush
  return 0;  // Return 0 indicates successful program termination
}
