#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::istringstream iss("Hello friends!");  // Initialize with a string
  std::cout << iss.str() << std::endl;

  std::string word;
  iss.str("Hello world!");  // Set a new string
  iss >> word;
  std::cout << iss.tellg() << " " << word << " " << iss.str() << std::endl;
  iss >> word;
  std::cout << iss.tellg() << " " << word << " " << iss.str() << std::endl;
  iss.clear();  // Clearing the EOF flag is needed if you want to reuse `iss`.

  std::ostringstream oss("Bye friends!");  // Initialize with a string
  std::cout << oss.str() << std::endl;
  oss.str("Bye world!");  // Set a new string
  std::cout << oss.str() << std::endl;
  return 0;
}
