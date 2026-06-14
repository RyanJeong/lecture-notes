#include <fstream>
#include <iostream>

int main() {
  std::ofstream ofstr("file_mode.txt");  // Open in default mode (out + trunc)
  ofstr << "This line will be overwritten." << std::endl;
  ofstr.close();

  ofstr.open("file_mode.txt", std::ios::out);  // out mode (trunc implicit)
  ofstr << "File mode is std::ios::out" << std::endl;
  ofstr.close();

  ofstr.open("file_mode.txt", std::ios::out | std::ios::app);  // out + app mode
  ofstr << "File mode is std::ios::out | std::ios::app" << std::endl;
  ofstr.close();

  std::ifstream ifstr("file_mode.txt");  // Open in default mode (in)
  while (ifstr) std::cout.put(ifstr.get());
  ifstr.close();
  return 0;
}
