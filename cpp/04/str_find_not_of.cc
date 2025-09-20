#include <iostream>
#include <string>

int main() {
  std::string sentence("The C++ language is fun to work with.");
  std::string set("aeiou");  // Vowels set for testing
  std::size_t pos;
  // Forward search for first character not from the character set
  pos = sentence.find_first_not_of(set);
  if (pos != std::string::npos)
    std::cout << "'" << sentence[pos] << "' found at position " << pos << "\n";
  else
    std::cout << "'" << sentence[pos] << "' not found\n";
  // Backward search for last character not from the character set
  pos = sentence.find_last_not_of(set);
  if (pos != std::string::npos)
    std::cout << "'" << sentence[pos] << "' found at position " << pos << "\n";
  else
    std::cout << "'" << sentence[pos] << "' not found\n";
  return 0;
}
