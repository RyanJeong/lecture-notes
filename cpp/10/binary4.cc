#include <fstream>
#include <iostream>
#include <string>

class Foo {
  int id_;
  double value_;
  std::string name_;

 public:
  Foo(int id, double value, const std::string& name)
      : id_(id), value_(value), name_(name) {}
  Foo() : id_(0), value_(0.0), name_(std::string()) {}

  // Serialize the object to a binary file.
  void Serialize(std::ofstream& out_file) const {
    out_file.write(reinterpret_cast<const char*>(&id_), sizeof(id_));
    out_file.write(reinterpret_cast<const char*>(&value_), sizeof(value_));
    size_t name_length = name_.size();  // Write the length of the string.
    out_file.write(reinterpret_cast<const char*>(&name_length),
                   sizeof(name_length));  // Write the string data.
    out_file.write(name_.c_str(), name_length);
  }

  // Deserialize the object from a binary file.
  void Deserialize(std::ifstream& in_file) {
    in_file.read(reinterpret_cast<char*>(&id_), sizeof(id_));
    in_file.read(reinterpret_cast<char*>(&value_), sizeof(value_));
    size_t name_length;  // Read the length of the string.
    in_file.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
    char* buffer = new char[name_length + 1];  // Read the string data.
    in_file.read(buffer, name_length);
    buffer[name_length] = '\0';  // Null-terminate the string.
    name_ = buffer;
    delete[] buffer;
  }

  void print() const {
    std::cout << "ID: " << id_ << ", Value: " << value_ << ", Name: " << name_
              << std::endl;
  }
};

int main() {
  const char* filename = "object_data_serialization.bin";

  Foo objects[] = {
      {1, 3.14, "Alice"},
      {2, 2.71, "Bob"},
      {3, 1.62, "Charlie"},
  };
  std::ofstream out_file(filename, std::ios::binary);
  if (!out_file.is_open()) {
    std::cerr << "Failed to open file for writing: " << filename << std::endl;
    return 1;
  }
  for (int i = 0; i < sizeof objects / sizeof(Foo); ++i)
    objects[i].Serialize(out_file);
  out_file.close();

  std::ifstream in_file(filename, std::ios::binary);
  if (!in_file.is_open()) {
    std::cerr << "Failed to open file for reading: " << filename << std::endl;
    return 1;
  }
  for (int i = 0; i < sizeof objects / sizeof(Foo); ++i) {
    Foo object;
    object.Deserialize(in_file);
    object.print();
  }
  in_file.close();

  return 0;
}