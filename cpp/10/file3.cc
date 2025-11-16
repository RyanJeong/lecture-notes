#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  const std::string filename = "file_stream_member_functions.txt";
  {
    std::ofstream file(filename);  // std::ios::out | std::ios::trunc
    if (!file.is_open()) {
      std::cerr << "The file " << filename << " cannot be opened for writing!";
      return 1;
    }
    file << "We have 42, 100, and 255 in this file." << std::endl;
    file.close();
  }  // std::ofstream will be removed automatically

  std::ifstream ifstr(filename, std::ios::in);
  ifstr.ignore(3);  // Skip 'W', 'e', and ' '
  std::cout << "Characters extracted so far: " << ifstr.gcount() << std::endl;
  for (char ch; ifstr.get(ch);) {
    if (std::isdigit(ch)) {
      ifstr.unget();  // Put back the digit character for proper extraction
      int n;
      ifstr >> n;
      std::cout << n << " ";
    }
  }
  ifstr.close();
  return 0;
}
