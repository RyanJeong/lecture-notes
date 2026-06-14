#include "tokenizer.hpp"

#include <string>

bool Tokenizer::MoreToken() const { return begin_ != std::string::npos; }

std::string Tokenizer::NextToken() {
  std::string token = target_.substr(begin_, end_ - begin_);
  begin_ = target_.find_first_not_of(delim_, end_);
  end_ = target_.find_first_of(delim_, begin_);
  return token;
}
