#pragma once

#include <string>

class Tokenizer {
 private:
  std::string target_;
  std::string delim_;
  std::size_t begin_;
  std::size_t end_;

 public:
  Tokenizer(const std::string& target, const std::string& delim)
      : target_(target),
        delim_(delim),
        begin_(target.find_first_not_of(delim, 0)),
        end_(target.find_first_of(delim, begin_)) {}

  bool MoreToken() const;   // Checks for more tokens
  std::string NextToken();  // Returns the next token
};
