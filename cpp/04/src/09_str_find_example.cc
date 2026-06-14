#include <iostream>
#include <string>

int main() {
  std::string str = "The quick brown fox jumps over the lazy dog";
  std::string search_str = "fox";
  // Using find to check if the string contains the substring (forward search)
  if (str.find(search_str) != std::string::npos)
    std::cout << "Found '" << search_str << "' using find." << std::endl;
  else
    std::cout << "Did not find '" << search_str << "' using find." << std::endl;
  // Using rfind to check if the string contains the substring (backward search)
  if (str.rfind(search_str) != std::string::npos)
    std::cout << "Found '" << search_str << "' using rfind." << std::endl;
  else
    std::cout << "Did not find '" << search_str << "' using rfind."
              << std::endl;
  return 0;
}
