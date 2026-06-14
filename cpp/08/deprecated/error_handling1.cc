#include <iostream>
#include <string>

int main() {
  try {
    std::string str("Hello");
    str.at(10);  // This will throw std::out_of_range

    std::stoi(str);  // This will throw std::invalid_argument, but it won't be
                     // executed because the previous line throws an exception.
  } catch (const std::out_of_range& e) {
    std::cerr << "Out of range error: " << e.what() << std::endl;
  } catch (const std::invalid_argument& e) {
    std::cerr << "Invalid argument error: " << e.what() << std::endl;
  }

  // The runtime allocates the exception object in an implementation-defined
  // location (not on the stack), allowing it to persist through stack unwinding
  // until it is handled.
  try {
    throw 1;  // it copies to exception storage as a temp object (1 is literal)
  } catch (int e) {  // int e = 1 (a copy from the exception storage)
    std::cerr << "Caught an exception with value: " << e << std::endl;
  }

  try {
    throw std::string("String exception");  // it copies to exception storage
  } catch (const std::string& e) {  // const std::string& e = std::string(...)
                                    // (a copy from the exception storage)
    std::cerr << "Caught a string exception: " << e << std::endl;
  }
  return 0;
}
