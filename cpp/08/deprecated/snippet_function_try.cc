#ifdef CPP_08_NOBUILD
ClassName::ClassName() try
    : member1_(/* initialization */), member2_(/* initialization */) {
  // Constructor body
} catch (const ExceptionType& e) {
  // Handle exception
}

#include <iostream>
#include <string>

class MyClass {
  int i_;
  int j_;

 public:
  MyClass() try : i_(0), j_(0) {
    if (i_ == 0) throw std::string("Integer is zero");
    // Case 1: i_ == 0 -> Exception thrown
    // Case 2: i_ != 0 -> No exception thrown
  } catch (const std::string& e) {
    std::cerr << "Handled: " << e << std::endl;
    // No re-throw -> Constructor completes normally
  }
  // Function-try block ends here!
  // -> Case 1 and Case 2 both reach here
  // -> Compiler generates destructor call registration at this point:
  // __runtime_register_destructor(this, &MyClass::~MyClass);
  ~MyClass() {
    // It will be called when the object is destroyed by cleanup_stack
  }
};

class MyClass {
  int i_;
  int j_;

 public:
  MyClass() try : i_(0), j_(0) {
    if (i_ == 0) throw std::string("Integer is zero");
    // Case 1: i_ == 0 -> Exception thrown
    // Case 2: i_ != 0 -> No exception thrown
  } catch (const std::string& e) {
    throw;
    // Re-throw -> Constructor does not complete normally
  }
  // Function-try block ends here!
  // -> Only Case 2 reaches here (case 1 object is incomplete)
  // -> Compiler generates destructor call registration at this point:
  // __runtime_register_destructor(this, &MyClass::~MyClass);
  ~MyClass() {
    // It will be called when the object is destroyed by cleanup_stack
  }
};
#endif  // CPP_08_NOBUILD
