#include <iostream>
#include <string>

class User {
  std::string name_;

 public:
  explicit User(const std::string& name) : name_(name) {}

  std::string name() const { return name_; }
};

class MessageSender {
 public:
  void SendMessage(const std::string& message, const User& user) {
    std::cout << "Sending message to " << user.name() << ": " << message
              << std::endl;
  }
};

int main() {
  User user("Ben");
  MessageSender sender;
  sender.SendMessage("Hello!", user);
  return 0;
}
