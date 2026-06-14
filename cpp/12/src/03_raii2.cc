#include <iostream>
#include <memory>  // for std::unique_ptr

#include "data_buffer.hpp"

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  try {
    std::unique_ptr<DataBuffer> buffer(new DataBuffer(1000));
    buffer->Process();  // Exception thrown!
  } catch (const std::exception& e) {
    std::cout << "Caught: " << e.what() << "\n";
  }
  // No need to delete;
  // The `buffer` object is automatically deleted when scope exits
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::cout << "RAII ensures cleanup!\n";
  return 0;
}
