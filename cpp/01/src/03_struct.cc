#include <iostream>

struct Point {
  int x, y;
};

int main() {
  struct Point p1 = {1, 2};  // C style
  Point p2 = {3, 4};         // C++ style
  std::cout << "(" << p1.x << ", " << p1.y << ")\n";
  std::cout << "(" << p2.x << ", " << p2.y << ")\n";
  return 0;
}