#if 1               /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <fstream>  // for std::ifstream, std::ofstream, std::fstream
#endif              /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Foo() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::ifstream input_stream;
  std::ofstream output_stream;
  std::fstream input_output_stream;

  input_stream.open("input.txt");
  output_stream.open("output.txt");
  input_output_stream.open("inout.txt");
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  input_stream.is_open();
  output_stream.is_open();
  input_output_stream.is_open();
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  input_stream.close();
  output_stream.close();
  input_output_stream.close();
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}
