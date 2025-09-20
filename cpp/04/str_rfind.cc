#include <iostream>
#include <string>

int main() {
  std::string str("The C++ language is fun to work with.");
  const char search_char = '+';
  std::size_t pos;
  // Backward search
  pos = str.rfind(search_char);  // find from the index str.size() - 1
  if (pos != std::string::npos)
    std::cout << "'" << search_char << "' found at position " << pos << "\n";
  else
    std::cout << "'" << search_char << "' not found\n";
  pos = str.rfind(search_char, 4);  // find from the index 4
  if (pos != std::string::npos)
    std::cout << "'" << search_char << "' found at position " << pos << "\n";
  else
    std::cout << "'" << search_char << "' not found\n";
  return 0;
}
