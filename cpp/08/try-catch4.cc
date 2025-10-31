#include <iostream>
#include <stdexcept>  // for std::invalid_argument, std::out_of_range

void ProcessData(int type) {
  if (type == 1) throw std::invalid_argument("Invalid argument");
  if (type == 2) throw std::out_of_range("Out of range");
  if (type == 3) throw 42;
  std::cout << "Data processed successfully" << std::endl;
}

int main() {
  for (int i = 1; i <= 4; ++i) {
    try {
      ProcessData(i);
    } catch (const std::invalid_argument& e) {
      std::cerr << "Caught specific exception: " << e.what() << std::endl;
    } catch (...) {  // Ellipsis catch-all handler; catches any exception type
      std::cerr << "Caught unknown exception type" << std::endl;
    }
  }
  return 0;
}
