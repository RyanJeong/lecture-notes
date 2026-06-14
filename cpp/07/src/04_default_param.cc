#include <iostream>
#include <string>

void Display(const std::string& msg = "Hello, world!") {
  std::cout << msg << std::endl;
}

int main() {
  Display();              // Uses default parameter
  Display("Hello C++!");  // Overrides default parameter
  return 0;
}
