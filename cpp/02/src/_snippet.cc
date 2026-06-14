#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Person {
  // Data members of classes, both static and non-static, are named like
  // ordinary non-member variables, but with a trailing underscore.
 public:
  char first_name_[32];
  char middle_name_[32];
  char last_name_[32];
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
struct Person {
  // Data members of structs, both static and non-static, are named like
  // ordinary non-member variables. They do not have the trailing underscores
  // that data members in classes have.
  char first_name[32];
  char middle_name[32];
  char last_name[32];
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#include <iostream>

void Print(int i) { std::cout << i << std::endl; }
void Print(double d) { std::cout << d << std::endl; }

int main() {
  Print(5L);  // 5L: long type

  // Converting long to int could potentially cause data loss.
  // Converting long to double is a safer conversion. Nevertheless, even
  // converting to double can still involve some degree of potential loss of
  // precision. Both cases have the same priority; hence, ambiguity arises.
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Circle {
 public:
  explicit Circle(double radius);  // Parameter Constructor
  Circle();                        // Default Constructor
  Circle(const Circle& circle);    // Copy Constructor
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Circle {
 public:
  explicit Circle(double radius)
      : radius_(radius), pi_(3.14) {}  // Initialization list

 private:
  double radius_;
  const double pi_;  // Constant value for Pi
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Circle {
 public:
  explicit Circle(double radius);  // Parameter Constructor
  Circle();                        // Default Constructor
  Circle(const Circle& circle);    // Copy Constructor

  ~Circle();  // Destructor
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
double Circle::get_radius(Circle* this) const { return this->radius_; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Snippet1(void) {
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Circle circle;
  Circle* this = &circle;
  circle.get_radius(this);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Rectangle {
  static int count_;  // declaration of static data member

 public:
  Rectangle() = default;
};

int Rectangle::count_ = 0;  // initialization of static data member
#endif                      /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
