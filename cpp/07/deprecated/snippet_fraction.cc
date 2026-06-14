#ifdef CPP_07_NOBUILD
#include "fraction/fraction.hpp"

void SnippetFraction() {
  Fraction f1(3, 4);
  Fraction f2(1, 2);

  f1.Add(f2);  // Using member function
  f1 + f2;     // Using overloaded + operator
}

#endif  // CPP_07_NOBUILD
