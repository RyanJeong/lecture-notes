#include <iostream>

#include "file_handle.hpp"

int main() {
  try {
    {
      FileHandle file("example.txt");
      // Even if an exception occurs, the file closes when scope exits
    }  // File is automatically closed here
    std::cout << "File handling is safe!\n";
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << "\n";
  }
  return 0;
}
