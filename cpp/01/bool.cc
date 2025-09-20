// C++: using built-in bool
#include <iostream>

int main() {
  bool done = false;  // boolean flag
  int count = 0;
  while (!done) {
    std::cout << "Count = " << count << std::endl;
    if (count >= 2) done = true;
    ++count;
  }
  return 0;
}
