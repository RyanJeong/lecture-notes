#include <iostream>
#include <string>

int main() {
  std::string greeting("Hello my friends");  // Creating a string object
  // Test size, maximum size, and capacity
  std::cout << "Size: " << greeting.size() << std::endl;
  std::cout << "Maximum size: " << greeting.max_size() << std::endl;
  std::cout << "Capacity: " << greeting.capacity() << std::endl;
  std::cout << "Empty? " << std::boolalpha << greeting.empty() << std::endl;
  std::cout << std::endl;
  // Making a reservation and testing again
  greeting.reserve(20);
  std::cout << "Size: " << greeting.size() << std::endl;
  std::cout << "Maximum size: " << greeting.max_size() << std::endl;
  std::cout << "Capacity: " << greeting.capacity() << std::endl;
  std::cout << "Empty? " << std::boolalpha << greeting.empty() << std::endl;
  return 0;
}
