#include <iostream>
#include <string>

int main() {
  // Constructing a default object
  std::string input_str;

  // Creating a string made of a single line
  std::cout << "Enter a line of characters: " << std::endl;
  std::getline(std::cin, input_str);
  std::cout << input_str << std::endl << std::endl;

  // Creating a string made of multiple lines
  std::cout << "Enter lines of characters ended with $: " << std::endl;
  std::getline(std::cin, input_str, '$');
  std::cout << input_str;
  return 0;
}
