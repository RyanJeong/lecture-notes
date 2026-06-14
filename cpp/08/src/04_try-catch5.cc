#include <iostream>
#include <stdexcept>

void Level3() { throw std::runtime_error("Error at Level3"); }

void Level2() {
  Level3();  // No try-catch: exception propagates
}

void Level1() {
  Level2();  // No try-catch: exception propagates
}

int main() {
  try {
    Level1();
  } catch (const std::invalid_argument& e) {
    // This catch block won't handle std::runtime_error; program will terminate
    std::cerr << "Caught: " << e.what() << std::endl;
  }
  return 0;
}
