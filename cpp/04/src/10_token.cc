#include <iostream>
#include <string>

int main() {
  std::string line;
  std::string delimiters = " \n";  // 2 delimiters: ' ', '\n'

  std::cout << "Enter a line: " << std::endl;
  std::getline(std::cin, line);

  // `end` is initialized to 0 for the first iteration
  std::string::size_type start, end = 0;  // positions of a word
  std::cout << "Words in the line:" << std::endl;
  while ((start = line.find_first_not_of(delimiters, end)) !=
         std::string::npos) {  // Find the start of the next word
    end = line.find_first_of(delimiters, start);  // Find the end of the word
    if (end == std::string::npos)
      end = line.size();  // Use the end of the string as our endpoint
    std::cout << line.substr(start, end - start) << std::endl;  // Extract word
  }
  return 0;
}
