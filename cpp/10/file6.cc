#include <cctype>
#include <fstream>
#include <iostream>

int main() {
  const char* filename = "sentence.txt";

  std::ofstream out_file(filename);
  out_file << "There are wonderful things to do in life.";
  out_file.close();

  std::fstream fstr(filename);  // Open for both reading and writing
  for (char ch; fstr.get(ch); std::cout << ch) {
    if (std::isspace(ch)) {
      ch = '\n';
      fstr.seekp(-1, std::ios::cur);
      fstr.put(ch);  // A space in the file is replaced with a newline.
    }
  }
  fstr.close();
  return 0;
}
