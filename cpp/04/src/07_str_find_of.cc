#include <iostream>
#include <string>

int main() {
  std::string str("The C++ language is fun to work with.");
  std::string set("aeiou");  // Vowels set for testing
  std::size_t pos;
  // Forward search for first character from the character set
  pos = str.find_first_of(set);
  if (pos != std::string::npos)
    std::cout << "'" << str[pos] << "' found at position " << pos << "\n";
  else
    std::cout << "'" << str[pos] << "' not found\n";
  // Backward search for last character from the character set
  pos = str.find_last_of(set);
  if (pos != std::string::npos)
    std::cout << "'" << str[pos] << "' found at position " << pos << "\n";
  else
    std::cout << "'" << str[pos] << "' not found\n";
  return 0;
}
