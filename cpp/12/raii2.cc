#include <iostream>
#include <memory>  // for std::unique_ptr

#include "data_buffer.hpp"

int main() {
  try {
    std::unique_ptr<DataBuffer> buffer(new DataBuffer(1000));
    buffer->Process();  // Exception thrown!
  } catch (const std::exception& e) {
    std::cout << "Caught: " << e.what() << "\n";
  }
  // No need to delete;
  // The `buffer` object is automatically deleted when scope exits
  std::cout << "RAII ensures cleanup!\n";
  return 0;
}
