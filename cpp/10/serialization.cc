#include <fstream>
#include <iostream>
#include <string>

int main() {
  const char* filename = "string_data.bin";

  {
    std::ofstream out_file(filename, std::ios::binary);
    std::string name = "Forouzan";

    int len = name.size();
    out_file.write(reinterpret_cast<const char*>(&len), sizeof(int));
    out_file.write(name.c_str(), name.size());
    out_file.close();
    // Serialization done (order: length, data)
  }

  {
    std::ifstream in_file(filename, std::ios::binary);

    int read_len = -1;
    in_file.read(reinterpret_cast<char*>(&read_len), sizeof(int));

    char* buffer = new char[read_len + 1];
    in_file.read(buffer, read_len);
    buffer[read_len] = '\0';  // Null-terminate the string

    std::cout << "Name: " << buffer << std::endl;

    delete[] buffer;
    in_file.close();
  }
  return 0;
}
