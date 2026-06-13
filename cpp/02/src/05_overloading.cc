#include <iostream>

// Volume of a cube.
int Volume(int s) { return s * s * s; }
// Volume of a cylinder.
double Volume(double r, int h) { return 3.1415926 * r * r * h; }
// Volume of a cuboid.
long Volume(long l, int b, int h) { return l * b * h; }

int main() {
  std::cout << Volume(10) << std::endl;
  std::cout << Volume(2.5, 8) << std::endl;
  std::cout << Volume(100l, 75, 15) << std::endl;
  return 0;
}