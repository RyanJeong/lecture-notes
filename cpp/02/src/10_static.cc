#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Rectangle {
  static int count_;  // declaration of static data member

 public:
  Rectangle() = default;
  static int get_count() { return count_; }  // static member function
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

int Rectangle::count_ = 0;  // initialization of static data member

void foo() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  int count = Rectangle::get_count();  // Call static member function
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) count;  // Avoid unused variable warning.
}

void bar() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  Rectangle rect;
  int count = rect.get_count();  // Call static member function
#endif                           /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) count;  // Avoid unused variable warning.
}