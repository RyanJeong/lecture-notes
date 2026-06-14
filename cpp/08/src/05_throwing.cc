#include <iostream>
#include <stdexcept>  // for std::invalid_argument

void ProcessData(int size) {
  const int expected_size = 10;

  int* data = new int[size];  // Allocate an array of integers
  try {
    if (size != expected_size) throw std::invalid_argument("Size mismatch");
    std::cout << "Processing " << size << " elements" << std::endl;
  } catch (const std::invalid_argument& e) {
    delete[] data;  // Cleanup before rethrowing
    throw;          // Re-throw to caller
  }
  delete[] data;  // Normal cleanup
}

int main() {
  try {
    ProcessData(5);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Main: " << e.what() << std::endl;
  }
  return 0;
}
