#include <iostream>
#include <map>  // for std::map
#include <string>

int main() {
  std::map<std::string, int> freq;
  std::string word;

  std::cout << "Enter words (EOF to exit): ";
  while (std::cin >> word)
    freq[word]++;  // Insert if not exists, then increment

  // Map iterates in sorted order (by key)
  // Elements are std::pair<const Key, Value>
  for (const auto& p : freq) std::cout << p.first << ": " << p.second << "\n";
  return 0;
}
