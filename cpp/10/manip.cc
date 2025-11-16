#ifdef CPP_10_NOBUILD
std::ostream& std::ostream::operator<<(
    std::ostream& (*manip_func)(std::ostream&) );
std::istream& std::istream::operator>>(
    std::istream& (*manip_func)(std::istream&) );
#endif  // CPP_10_NOBUILD

#include <iomanip>
#include <iostream>

int main() {
  double pi = 3.14159265358979323846;
  // Fixed-point notation with 4 decimal places
  std::cout << "Fixed (4 decimal places): " << std::fixed
            << std::setprecision(4) << pi << std::endl;  // 3.1416
  return 0;
}
