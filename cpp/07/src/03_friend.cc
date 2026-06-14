#include <iostream>

class MyClass {
  int data_;

 public:
  explicit MyClass(int data) : data_(data) {}

  friend void FriendFunction(const MyClass& obj);

 private:
  void PrivateFunction() const {
    std::cout << "Private member function called\n";
  }
};

// Friend function definition
void FriendFunction(const MyClass& obj) {
  std::cout << "Accessing private data: " << obj.data_ << "\n";
  obj.PrivateFunction();
}

int main() {
  MyClass obj(10);
  FriendFunction(obj);  // Calls FriendFunction to access private members
  return 0;
}
