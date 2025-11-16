#include <fstream>
#include <iostream>

int main() {
  // 1. Instantiation of an ofstream object (not opened yet)
  std::ofstream ofstr;
  // 2. Creation of a file and connecting it to the std::ofstream object
  ofstr.open("file_stream.txt");
  if (!ofstr.is_open()) {
    std::cerr << "file_stream.txt cannot be opened!";
    return 1;
  }
  // 3. Writing to the file using overloaded insertion operator
  for (int i = 1; i <= 10; ++i) ofstr << i * 10 << " ";
  // 4. Disconnection of the file_stream.txt from the std::ofstream object
  ofstr.close();
  return 0;  // 5. The std::ofstream object is destroyed after return statement
}
