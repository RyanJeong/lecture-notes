#include <fstream>
#include <iostream>

int main() {
  const char* filename = "sentence.txt";
  // open the file in output mode with the "ate" (at end) mode flag to get the
  // file size.
  std::fstream fstr(filename, std::ios::out | std::ios::ate);
  std::cout << "File size: " << fstr.tellg();
  fstr.close();
  return 0;
}
