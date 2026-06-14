#include <fstream>
#include <iostream>

class Foo {
  int id_;
  double value_;

 public:
  Foo(int id, double value) : id_(id), value_(value) {}
  Foo() : id_(0), value_(0.0) {}  // Default constructor for reading
  void print() const {
    std::cout << "ID: " << id_ << ", Value: " << value_ << std::endl;
  }
};

int main() {
  const char* filename = "object_data.bin";

  Foo obj_out(527, 3.14);
  // 1. The default mode of std::ofstream is std::ios::out | std::ios::trunc.
  // 2. To open the file in binary mode, std::ios::binary is added.
  // -> std::ios::out | std::ios::trunc | std::ios::binary
  std::ofstream out_file(filename, std::ios::binary);
  if (out_file.is_open()) {
    out_file.write(reinterpret_cast<char*>(&obj_out), sizeof(obj_out));
    out_file.close();
  }

  Foo obj_in;
  // `in_file` will be opened in std::ios::in | std::ios::binary mode
  std::ifstream in_file(filename, std::ios::binary);
  if (in_file.is_open()) {
    in_file.read(reinterpret_cast<char*>(&obj_in), sizeof(obj_in));
    in_file.close();
  }
  obj_in.print();
  return 0;
}
