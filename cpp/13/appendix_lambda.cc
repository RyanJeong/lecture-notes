#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::vector<std::function<void()>> tasks;

  // Two lambdas have different types even though they have the same signature
  // and body
  tasks.push_back([]() -> void { std::cout << "Task 1\n"; });
  tasks.push_back([]() -> void { std::cout << "Task 2\n"; });

  for (auto& f : tasks) f();  // Run each lambda
  return 0;
}

void Appendix1() {
  // Two lambdas have different types even though they have the same signature
  // and body
  auto lambda1 = []() -> void { std::cout << "Task 1\n"; };
  auto lambda2 = []() -> void { std::cout << "Task 2\n"; };
}

class EventHandler {
  // Store any callable with no parameters and no return value
  std::function<void()> callback_;

 public:
  void SetCallback(std::function<void()> cb) { callback_ = cb; }

  void TriggerEvent() {
    if (callback_) callback_();
  }
};
