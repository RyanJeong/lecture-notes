#include <iostream>
#include <string>

int main() {
  try {
    std::string str_number;
    std::cout << "Enter a number: ";
    std::cin >> str_number;
    std::cout << "Entered: " << std::stoi(str_number);
  } catch (const std::invalid_argument& e) {
    // Re-throw the caught exception; the program will terminate because the
    // exception is passed to the runtime system.
    throw;
  }
  return 0;
}
