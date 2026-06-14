#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class FileHandle {
  std::fstream file_;

 public:
  explicit FileHandle(const std::string& filename) {
    file_.open(filename, std::ios::in | std::ios::out | std::ios::app);
    if (!file_.is_open()) throw std::runtime_error("Can't open " + filename);
    std::cout << "File opened: " << filename << std::endl;
  }
  ~FileHandle() {
    if (file_.is_open()) file_.close();
    std::cout << "File closed" << std::endl;
  }
};
