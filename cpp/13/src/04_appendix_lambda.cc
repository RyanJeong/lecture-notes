#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
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
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

void Appendix1() {
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // Two lambdas have different types even though they have the same signature
  // and body
  auto lambda1 = []() -> void { std::cout << "Task 1\n"; };
  auto lambda2 = []() -> void { std::cout << "Task 2\n"; };
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

  (void) lambda1;
  (void) lambda2;
}

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
class EventHandler {
  // Store any callable with no parameters and no return value
  std::function<void()> callback_;

 public:
  void SetCallback(std::function<void()> cb) { callback_ = cb; }

  void TriggerEvent() {
    if (callback_) callback_();
  }
};
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
