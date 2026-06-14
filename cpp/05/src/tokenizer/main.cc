#include <iostream>
#include <string>

#include "tokenizer.hpp"

int main() {
  // The `target` string is the one that needs to be tokenized.
  std::string target = "This is the string to be tokenized. \n";
  // The `delimit` string specifies the set of separators, including space and
  // newline characters.
  std::string delimit = " \n";

  // Instantiation of tokenizer object
  Tokenizer tokenizer(target, delimit);

  // Traversing the target string to find tokens
  while (tokenizer.MoreToken()) std::cout << tokenizer.NextToken() << std::endl;
  return 0;
}
