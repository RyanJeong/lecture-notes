#include <iostream>

class Circle {
  double radius_;  // Data member (using the default access specifier - private)

 public:  // Member functions
  void set_radius(double radius);
  double get_radius() const;
};  // A semicolon is needed at the end of class definition

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
double Circle::get_radius() const { return radius_; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#if 1  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void Circle::set_radius(double r) { radius_ = r; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int main() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Circle circle;
  circle.set_radius(10);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::cout << circle.get_radius() << std::endl;
  return 0;
}
