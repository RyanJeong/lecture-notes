#include <iostream>
#include <map>  // for std::map
#include <string>

// 1. Key Type: Must define operator< for sorting order
struct Key {
  int id;
  bool operator<(const Key& other) const { return id < other.id; }
};

// 2. Value Type: No comparison operators needed
struct Val {
  std::string data;
};

int main() {
  // std::map: Key needs operator<, Val does not
  std::map<Key, Val> m;
  m[{2}] = {"Hello"};  // Valid: Key is sortable, Val is just payload
  std::cout << "Map Val: " << m[{2}].data << std::endl;
  return 0;
}
