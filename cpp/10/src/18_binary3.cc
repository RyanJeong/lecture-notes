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
  const char* filename = "object_data_random_access.bin";

  Foo objs_out[] = {{527, 3.14}, {920, 1.414}, {777, 1.732}};
  std::ofstream out_file(filename, std::ios::binary);
  if (out_file.is_open()) {
    for (size_t i = 0; i < sizeof objs_out / sizeof(Foo); ++i)
      out_file.write(reinterpret_cast<char*>(&objs_out[i]), sizeof(Foo));
    out_file.close();
  }

  Foo obj_in;
  std::ifstream in_file(filename, std::ios::binary);
  if (in_file.is_open()) {
    // Read the second object: {920, 1.414}
    in_file.seekg(sizeof(Foo), std::ios::beg);  // offset: sizeof(Foo)
    in_file.read(reinterpret_cast<char*>(&obj_in), sizeof(obj_in));
    in_file.close();
  }
  obj_in.print();
  return 0;
}
