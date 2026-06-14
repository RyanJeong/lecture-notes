#include <map>  // for std::map
#include <string>

int main() {
  std::map<std::string, int> freq;

  // 1. Query existing key (safe)
  if (freq.find("apple") != freq.end()) {
    int count = freq["apple"];  // Already exists
    (void) count;
  }

  // 2. Insert new key (unintended insertion occurs)
  int value = freq["banana"];  // Key does not exist, auto-created, so value = 0
                               // `freq` now contains { "banana": 0 }
  (void) value;
  return 0;
}