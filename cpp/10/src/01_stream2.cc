#include <iostream>
#include <limits>  // for std::numeric_limits

int main() {
  int i;
  std::cout << "Enter an integer: ";
  std::cin >> i;

  if (std::cin.fail()) {
    std::cin.clear();  // Clear the error flag to recover from the fail state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Please enter an integer again: ";
    std::cin >> i;
    if (std::cin.fail()) {
      std::cerr << "[Error] Still not a valid integer. Exiting." << std::endl;
      return 1;
    }
  }
  std::cout << "You entered: " << i << std::endl;
  return 0;
}
