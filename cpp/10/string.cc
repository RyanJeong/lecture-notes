#include <iostream>
#include <sstream>

int main() {
  std::istringstream in_stream;

  // Set the content of the input string stream
  in_stream.str("123 45.67 Forouzan");
  int i;
  double d;
  in_stream >> i >> d;
  std::cout << "Integer: " << i << std::endl;
  std::cout << "Double: " << d << std::endl;

  std::ostringstream out_stream;
  out_stream << "Integer: " << i << std::endl;
  out_stream << "Double: " << d << std::endl;

  // Get the content of the output string stream
  std::cout << out_stream.str();

  return 0;
}