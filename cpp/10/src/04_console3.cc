#include <cctype>  // for std::isspace
#include <iostream>

int main() {
  // 1. Use int get(void) to read characters one by one
  std::cout << "Enter a character: ";
  char c = std::cin.get();
  std::cout << "You entered: " << c << std::endl;

  std::cin.ignore();  // consume a '\n' from the input stream buffer

  // 2. Use istream& get(char& c) to read characters one by one
  //    Use ostream& put(char c) to write characters one by one
  std::cout << "Enter a word: ";
  for (char ch; std::cin.get(ch); std::cout.put(ch))
    if (std::isspace(ch)) break;

  return 0;
}
