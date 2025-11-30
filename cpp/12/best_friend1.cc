#include <iostream>
#include <memory>  // for std::shared_ptr, std::make_shared
#include <string>

class Person {
 public:
  std::string name_;
  std::shared_ptr<Person> best_friend_;

  explicit Person(std::string n) : name_(n) {
    std::cout << name_ << " is born" << std::endl;
  }
  ~Person() { std::cout << name_ << " is destroyed" << std::endl; }

  void BecomesBestFriendOf(std::shared_ptr<Person> p) {
    // If we do this, the system creates a "new control block" to manage this
    // object separately.
    p->best_friend_ = std::shared_ptr<Person>(this);
  }
};

int main() {
  // 1. Create Alice and Bob (each creates a control block)
  std::shared_ptr<Person> alice = std::make_shared<Person>("Alice");
  std::shared_ptr<Person> bob = std::make_shared<Person>("Bob");

  // 2. Alice sends best friend request to Bob
  alice->BecomesBestFriendOf(bob);
  std::cout << "Alice's strong count: " << alice.use_count() << std::endl;
  std::cout << "Bob's strong count: " << bob.use_count() << std::endl;

  // 3. At the end of main (disaster occurs)
  // - `bob` is destroyed -> Bob's best_friend_(Alice) tries to destroy
  //                         Alice (Alice dies 1st time)
  // - `alice` variable is destroyed -> The original pointer managing Alice
  //                                    tries to destroy Alice
  //                                    (Alice dies 2nd time)
  // -> Crash! (Double Free error)
  return 0;
}
