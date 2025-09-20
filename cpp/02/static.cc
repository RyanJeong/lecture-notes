class Rectangle {
  static int count_;  // declaration of static data member

 public:
  Rectangle() = default;
};

int Rectangle::count_ = 0;  // initialization of static data member

#ifdef CPP_02_NOBUILD
class Rectangle {
  static int count_;  // declaration of static data member

 public:
  Rectangle() = default;
  static int get_count() { return count_; }  // static member function
};

int Rectangle::count_ = 0;  // initialization of static data member

void foo() {
  int count = Rectangle::get_count();  // Call static member function
}

void bar() {
  Rectangle rect;
  int count = rect.get_count();  // Call static member function
}
#endif  // CPP_02_NOBUILD
