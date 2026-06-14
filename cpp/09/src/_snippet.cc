#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Template-declaration: template <template-parameters> declaration
template <typename T, typename X, typename Y, typename Z>
T FunctionTemplateSyntax(X first, Y second, Z last) {
  // do something ...
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Definition of a template function
template <typename T>
T Smaller(const T& op1, const T& op2) {
  return op1 < op2 ? op1 : op2;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Function to find the smaller between two characters
char Smaller(char op1, char op2) { return op1 < op2 ? op1 : op2; }

// Function to find the smaller between two integers
int Smaller(int op1, int op2) { return op1 < op2 ? op1 : op2; }

// Function to find the smaller between two doubles
double Smaller(double op1, double op2) { return op1 < op2 ? op1 : op2; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Default argument for type template parameters
template <typename T1, typename T2 = int>
T1 DefaultArgumentTemplate(T1 obj, T2 size);

// Default argument for non-type template parameters
template <typename T, int n, int step = 1>
T DefaultNonTypeTemplate(T (&array)[n]);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet1() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Smaller(12.34, 15);          // Smaller(double, int) -> T can't be deduced
  Smaller<double>(12.34, 15);  // Explicitly specify T as double
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

void Snippet2() {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Smaller("apple", "banana");      // const char* can't be compared directly
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#include <cstring>

#if 1        /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
template <>  // Specialization for const char*
const char* Smaller(const char* const& op1, const char* const& op2) {
  return std::strcmp(op1, op2) < 0 ? op1 : op2;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include "stack/stack.hpp"

void Snippet3() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // using new_type_name = existing_type_name;
  using StackInt = Stack<int>;  // Alias for Stack<int>
  StackInt stack(5);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) stack; /* Avoid unused variable warning. */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Note: Template aliases (using) cannot be defined in local (block) scope.
template <typename T>
using Ptr = T*;  // Alias for pointer to `T`

int x = 42;
Ptr<int> p = &x;  // Using the `Ptr` alias
#endif            /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
namespace std {
using string = basic_string<char, std::char_traits<char>, std::allocator<char>>;
}  // namespace std
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
namespace std {
using string = basic_string<char>;  // C++14 std::string alias
}  // namespace std
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
namespace std {
using istream = basic_istream<char>;
using ostream = basic_ostream<char>;
}  // namespace std
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
