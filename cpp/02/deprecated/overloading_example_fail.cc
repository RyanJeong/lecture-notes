#ifdef CPP_02_NOBUILD
#include <iostream>

void Print(int i) { std::cout << i << std::endl; }
void Print(double d) { std::cout << d << std::endl; }

int main() {
  Print(5L);  // 5L: long type

  // Converting long to int could potentially cause data loss.
  // Converting long to double is a safer conversion. Nevertheless, even
  // converting to double can still involve some degree of potential loss of
  // precision. Both cases have the same priority; hence, ambiguity arises.
  return 0;
}
#endif  // CPP_02_NOBUILD
