#ifdef CPP_12_NOBUILD
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
#endif  // CPP_12_NOBUILD
