#include <fstream>  // for std::ifstream, std::ofstream, std::fstream

void Foo() {
  std::ifstream input_stream;
  std::ofstream output_stream;
  std::fstream input_output_stream;

  input_stream.open("input.txt");
  output_stream.open("output.txt");
  input_output_stream.open("inout.txt");

  input_stream.is_open();
  output_stream.is_open();
  input_output_stream.is_open();

  input_stream.close();
  output_stream.close();
  input_output_stream.close();
}
