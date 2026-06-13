#include <iostream>

int main() {
  char str[100];  // C-style string

  std::cout << "Enter a word: ";
  std::cin >> str;  // Read a single word (no spaces) into the C-style string
  std::cout << "Entered word: " << str << "\n";

  std::cin.ignore();  // Clear the newline character from the input buffer

  std::cout << "Enter a sentence: ";
  std::cin.getline(str, 100);  // Maximum 99 characters + null terminator
  std::cout << "Entered sentence: " << str << '\n';
  return 0;
}
