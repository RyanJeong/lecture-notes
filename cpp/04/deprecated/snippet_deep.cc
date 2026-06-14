#include <cstring>

class DeepCopy {
  char* data_;

 public:
  explicit DeepCopy(const char* s) : data_(new char[std::strlen(s) + 1]) {
    std::strcpy(data_, s);  // Copy string data
  }
  // Copy constructor (deep copy): It copies the actual string data, not just
  // the pointer so that each object has its own copy of the data.
  DeepCopy(const DeepCopy& str) {
    data_ = new char[std::strlen(str.data_) + 1];  // Allocate new memory
    // Copy the actual string data, not just the pointer
    std::strcpy(data_, str.data_);
  }
  ~DeepCopy() {
    delete[] data_;  // Safe because each object has its own memory
  }
};

int main() {
  DeepCopy obj1("Hello");
  // deep copy occurs here - each object has its own memory
  DeepCopy obj2(obj1);  // it converts to DeepCopy obj2 = obj1; (implicit)
  // another deep copy
  DeepCopy obj3(obj1);  // it converts to DeepCopy obj3 = obj1; (implicit)
  return 0;
  // Each object has its own memory, so delete[] is called safely for each
  // without causing double-free errors
}
