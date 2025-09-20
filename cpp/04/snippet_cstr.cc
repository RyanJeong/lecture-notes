#ifdef CPP_04_NOBUILD
void foo1() {
  char str1[] = {'A', 'B', 'C', 'D', '\0'};  // Non-constant
  char str2[] = "ABCD";                      // Non-constant compact
  const char str4[] = "ABCD";                // Constant compact
  // const char str3[] = {'A', 'B', 'C', 'D', '\0'};  // Constant
}

void foo2() {
  char* str = "Hello";        // Error: Literal is a constant
  const char* str = "Hello";  // OK
}

void foo3() {
  // Memory Management:
  // C-strings require manual memory management, which can lead to issues like
  // memory leaks or buffer overflows.
  char* str = (char*) malloc(10);
  strcpy(str, "Hello, World!");  // Buffer overflow!
  free(str);
}

// String Length and Size:
// You need to traverse the entire string to compute its length, which can be
// inefficient for large strings since C-strings don't track their own size.

// strlen: return length of string `s`
int strlen(char* s) {
  char* p = s;

  while (*p) p++;

  return p - s;
}

void foo4() {
  char str[] = "Hello";
  int len = strlen(str);  // Traverse the entire string
}

void foo5() {
  // String Concatenation:
  // In C-strings, to concatenate, you need to ensure there's enough space and
  // use the strcat function.
  char buffer[20] = "Hello";
  strcat(buffer, ", World!");  // Always ensure buffer has enough space
}

void foo6() {
  // Substring Extraction and Replacement:
  // You need to ensure there's enough space and use the strncpy function.
  char str[] = "Hello, World!";
  char substring[6];
  strncpy(substring, str + 7, 5);  // Extract "World"
  substring[5] = '\0';             // Add null terminator

  char* pos = strstr(str, "World");  // Find the position of "World"
  if (pos) strncpy(pos, "C++", 3);   // Replace with "C++"
  // Note: If your replacement string is longer, ensure there's enough space
  // If your replacement string is shorter, manually do something to remove
  // leftover characters
  *(pos + 3) = '\0';  // "Hello, C++ld!" -> "Hello, C++"
}

#include <string>

void foo7() {
  std::string str = "abc";
  // memory: ['a']['b']['c']['?']['?']['?']

  str += "de";
  // memory: ['a']['b']['c']['d']['e']['?']

  str += "fg";
  // memory: ['a']['b']['c']['d']['e']['f']['g']['?']['?']['?']['?']['?']
}
#endif  // CPP_04_NOBUILD
