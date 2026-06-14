#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
namespace std {
ostream& ostream::operator<<(ostream& (*manip_func)(ostream&));
istream& istream::operator>>(istream& (*manip_func)(istream&));
}  // namespace std
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#include <iomanip>
#include <iostream>

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  double pi = 3.14159265358979323846;
  // Fixed-point notation with 4 decimal places
  std::cout << "Fixed (4 decimal places): " << std::fixed
            << std::setprecision(4) << pi << std::endl;  // 3.1416
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  return 0;
}
