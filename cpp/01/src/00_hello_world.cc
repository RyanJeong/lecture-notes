#if 1                /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>  // C++ standard input/output stream header
                     // Unlike C, C++ headers do not use file extensions
#endif               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int main() {
  std::cout << "Hello, world"  // std::cout: standard output stream object
            << std::endl;      // std::endl: manipulator for newline + flush
  return 0;  // Return 0 indicates successful program termination
}
