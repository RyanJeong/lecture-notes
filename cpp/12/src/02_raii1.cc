#include <iostream>

#include "data_buffer.hpp"

int main() {
  try {
    DataBuffer* buffer = new DataBuffer(1000);
    buffer->Process();  // If an exception is thrown here...
    delete buffer;      // ...this line is never reached
  } catch (const std::exception& e) {
    std::cout << "Caught: " << e.what() << "\n";
  }
  // The `buffer` object is never deleted; memory leak occurs.
  return 0;
}
