#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class Fraction;  // Forward declaration for the type you want to use

class SmartPtr {
  Fraction* ptr_;

 public:
  explicit SmartPtr(Fraction* p) : ptr_(p) {}
  ~SmartPtr() { delete ptr_; }

  Fraction& operator*() const { return *ptr_; }
  Fraction* operator->() const { return ptr_; }
};

int main() {
  SmartPtr sp(new Fraction(2, 5));
  (*sp).Print();
  sp->Print();  // `sp` is a stack instance; it's dtor will auto-invoke!
  return 0;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
