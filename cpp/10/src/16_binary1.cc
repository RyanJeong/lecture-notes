#include <fstream>
#include <iostream>

int main() {
  const char* filename = "double_data.bin";

  double double_out = 45.78;
  std::ofstream ofstr(filename, std::ios::out | std::ios::binary);
  if (!ofstr.is_open()) {
    std::cerr << "The file binary_test cannot be opened for writing!";
    return 1;
  }
  ofstr.write(reinterpret_cast<char*>(&double_out), sizeof(double));
  ofstr.close();  // $xxd binary_io.bin: a470 3d0a d7e3 4640

  double double_in;
  std::ifstream ifstr(filename, std::ios::in | std::ios::binary);
  ifstr.read(reinterpret_cast<char*>(&double_in), sizeof(double));
  ifstr.close();
  std::cout << "Value of double_in: " << double_in << std::endl;
  return 0;
}
