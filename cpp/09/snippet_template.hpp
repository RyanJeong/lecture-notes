#pragma once

#ifdef CPP_09_NOBUILD
template <typename T, typename X, typename Y, typename Z>
T FunctionTemplateSyntax(X first, Y second, Z last) {
  // do something ...
}

// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) {
  return op1 < op2 ? op1 : op2;
}

// Function to find the smaller between two characters
char Smaller(char op1, char op2) { return op1 < op2 ? op1 : op2; }

// Function to find the smaller between two integers
int Smaller(int op1, int op2) { return op1 < op2 ? op1 : op2; }

// Function to find the smaller between two doubles
double Smaller(double op1, double op2) { return op1 < op2 ? op1 : op2; }

// Non-type template parameter example
template <double D>  // The `double` type is allowed since C++20.
void TemplateNonTypeParameter() {
  // do something with D ...
}

void Foo() {
  // `0.1 + 0.2` and `0.3` may not be exactly equal
  TemplateNonTypeParameter<0.1 + 0.2>();  // Instantiation 1
  TemplateNonTypeParameter<0.3>();        // Instantiation 2
}

// Default argument for type template parameters
template <typename T1, typename T2 = int>
T1 DefaultArgumentTemplate(T1 obj, T2 size);

// Default argument for non-type template parameters
template <typename T, int n, int step = 1>
T DefaultNonTypeTemplate(T (&array)[n]);

void Bar() {
  Smaller(12.34, 15);          // Smaller(double, int) -> T can't be deduced
  Smaller<double>(12.34, 15);  // Explicitly specify T as double
}

#include <string>

void Qux() {
  Smaller(std::string("apple"),
          std::string("banana"));  // std::string has operator<
  Smaller("apple", "banana");      // const char* can't be compared directly
}

template <>  // Specialization for const char*
const char* Smaller(const char* const& op1, const char* const& op2) {
  return std::strcmp(op1, op2) < 0 ? op1 : op2;
}
#endif
