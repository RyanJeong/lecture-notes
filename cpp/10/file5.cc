#include <fstream>
#include <iostream>

int main() {
  const char* filename = "tellg_example.txt";

  std::ofstream out_file(filename);
  out_file << "Hello";  // 5 characters: 'H', 'e', 'l', 'l', 'o'
  out_file.close();

  std::ifstream in_file(filename);
  while (in_file) {
    std::cout << in_file.tellg() << '(' << static_cast<char>(in_file.get())
              << ')' << std::endl;
    std::cout << "  failbit: " << in_file.fail() << std::endl;
  }
  in_file.close();
  return 0;
}
