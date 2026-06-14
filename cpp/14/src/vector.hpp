#pragma once

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Basic vector structure (conceptual)
template <typename T>
class vector {
  T* data;           // Start address of allocated memory
  size_t size_;      // Number of actual elements stored
  size_t capacity_;  // Capacity of allocated memory

 public:
  T& operator[](size_t i) { return data[i]; }  // O(1) access
  void push_back(const T& val) {
    if (size_ == capacity_) {  // Capacity exceeded (it causes amortized O(1))
      capacity_ *= 2;          // Double the capacity
      T* newData = new T[capacity_];
      for (size_t i = 0; i < size_; ++i)
        newData[i] = data[i];  // Copy all elements
      delete[] data;
      data = newData;
    }
    data[size_++] = val;
  }
};
#endif  // DO NOT CONTAIN THIS LINE IN THE MARKDOWN
