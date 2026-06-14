#include <iostream>
#include <memory>  // for std::shared_ptr, std::make_shared,
                   // for std::enable_shared_from_this
#include <string>

class Person : public std::enable_shared_from_this<Person> {
 public:
  std::string name_;
  std::shared_ptr<Person> best_friend_;

  explicit Person(std::string n) : name_(n) {
    std::cout << name_ << " is born" << std::endl;
  }
  ~Person() { std::cout << name_ << " is destroyed" << std::endl; }

  void BecomesBestFriendOf(std::shared_ptr<Person> p) {
    p->best_friend_ = shared_from_this();
  }
};

int main() {
  // 1. Create Alice and Bob (each creates a control block)
  std::shared_ptr<Person> alice = std::make_shared<Person>("Alice");
  std::shared_ptr<Person> bob = std::make_shared<Person>("Bob");

  // 2. Alice sends best friend request to Bob and vice versa
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  alice->BecomesBestFriendOf(bob);
  bob->BecomesBestFriendOf(alice);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  std::cout << "Alice's strong count: " << alice.use_count() << std::endl;
  std::cout << "Bob's strong count: " << bob.use_count() << std::endl;

  // 3. At the end of main (memory leak due to circular reference!)
  return 0;
}