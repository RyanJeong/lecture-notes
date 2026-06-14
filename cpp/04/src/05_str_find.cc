#include <iostream>
#include <string>

int main() {
  std::string str("The C++ language is fun to work with.");
  const char search_char = 'C';
  std::size_t pos;
  // Forward search
  pos = str.find(search_char);  // find from the index 0
  if (pos != std::string::npos)
    std::cout << "'" << search_char << "' found at position " << pos << "\n";
  else
    std::cout << "'" << search_char << "' not found\n";
  pos = str.find(search_char, 5);  // find from the index 5
  if (pos != std::string::npos)
    std::cout << "'" << search_char << "' found at position " << pos << "\n";
  else
    std::cout << "'" << search_char << "' not found\n";
  return 0;
}
