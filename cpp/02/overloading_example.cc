#include <iostream>

void Print(int i) { std::cout << i << std::endl; }
void Print(double d) { std::cout << d << std::endl; }

int main() {
  Print('a');   // promoted (char -> int) and it matches Print(int)
  Print(true);  // promoted (bool -> int) and it matches Print(int)
  Print(4.5f);  // promoted (float -> double) and it matches Print(double)
  return 0;
}