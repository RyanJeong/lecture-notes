#pragma once

#include <memory>
#include <stdexcept>

class DataBuffer {
  int* data_;
  size_t size_;

 public:
  explicit DataBuffer(size_t size) : size_(size) { data_ = new int[size]; }
  ~DataBuffer() { delete[] data_; }

  void Process() { throw std::runtime_error("Processing error!"); }
};
