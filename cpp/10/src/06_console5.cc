#include <iostream>

int main() {
  char buffer[64];

  // 1. Using std::cin.get(char* s, int n)
  std::cout << "Enter a string (max 63 characters, stops at newline but "
               "doesn't remove it from the buffer): ";
  std::cin.get(buffer, 64);  // Reads up to 63 characters
  std::cout << "You entered (std::cin.get): " << buffer << std::endl;

  std::cin.ignore();  // Consumption of a newline left by get(buffer, 64)

  // 2. Using std::cin.getline(char* s, int n, char delim = '\n')
  std::cout << "Enter another string (max 63 characters, stops at newline "
               "(default delimiter) and removes it from the buffer): ";
  std::cin.getline(buffer,
                   64);  // Reads up to 63 characters
  std::cout << "You entered (std::cin.getline): " << buffer << std::endl;
  return 0;
}