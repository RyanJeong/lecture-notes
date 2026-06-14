#include <fstream>
#include <iostream>

int main() {
  const char* filename = "seekg_example.txt";
  std::ofstream out_file(filename);
  out_file << "example";  // 7 characters: 'e', 'x', 'a', 'm', 'p', 'l', 'e'
  out_file.close();

  std::ifstream in_file(filename);
  in_file.seekg(2, std::ios::beg);  // begin: 'e', position 2: 'a'
  char a = in_file.peek();
  in_file.seekg(2, std::ios::cur);  // current: 'a', position 2 ahead: 'p'
  char p = in_file.peek();
  in_file.seekg(1, std::ios::cur);  // current: 'p', position 1 ahead: 'l'
  char l = in_file.peek();
  in_file.seekg(-1, std::ios::end);  // end: after 'e', position -1: 'e'
  char e = in_file.peek();
  std::cout << a << p << p << l << e << std::endl;  // Output: apple
  in_file.close();
  return 0;
}
