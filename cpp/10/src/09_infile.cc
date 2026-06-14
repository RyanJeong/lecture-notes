#include <fstream>
#include <iostream>

int main() {
  // 1. Instantiation of an std::ifstream object (not opened yet)
  std::ifstream ifstr;
  // 2. Connection of the existing file to the std::ifstream object
  ifstr.open("file_stream.txt");
  if (!ifstr.is_open()) {  // opt. Testing opening success
    std::cerr << "file_stream.txt cannot be opened!";
    return 1;
  }
  // 3. Reading from the std::ifstream object
  for (int i = 1; i <= 10; ++i) {
    int data;
    ifstr >> data;
    std::cout << data << std::endl;
  }
  // 4. Disconnection of the file_stream.txt from the std::ifstream object
  ifstr.close();
  return 0;  // 5. The std::ifstream object is destroyed after return statement
}
