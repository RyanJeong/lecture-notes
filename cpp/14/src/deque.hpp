#pragma once

#include <iostream>  // for size_t

#if 1  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
// Basic deque structure (conceptual)
template <typename T, size_t BlockSize = 512>
class deque {
 private:
  T* blocks[256];    // Pointer array: each pointer references a memory block
  size_t front_idx;  // Block index of the first element
  size_t back_idx;   // Block index of the last element

 public:
  void push_front(const T& val) {
    // Space available at front, no data shifting needed
    blocks[front_idx][...] = val;
    front_idx--;  // O(1)
  }
  void push_back(const T& val) {
    // Space available at back, no data shifting needed
    blocks[back_idx][...] = val;
    back_idx++;  // O(1)
  }
};
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
