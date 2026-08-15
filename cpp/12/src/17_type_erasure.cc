#include <memory>  // for std::shared_ptr, std::allocator

// Custom allocator (standard inheritance for simplicity)
template <class T>
struct MyAlloc : std::allocator<T> {
  MyAlloc() = default;
  template <class U>
  MyAlloc(const MyAlloc<U>&) {}
  // Without this, the inherited rebind yields std::allocator<U>, not MyAlloc<U>
  template <class U>
  struct rebind {
    typedef MyAlloc<U> other;
  };
};

// Custom deleter (a simple lambda function)
auto del = [](int* p) { delete p; };

int main() {
  MyAlloc<int> alloc;

  // - `p1`: default allocator + custom deleter
  std::shared_ptr<int> p1(new int(10), del);
  // - `p2`: custom allocator (for control block) + custom deleter
  std::shared_ptr<int> p2(new int(20), del, alloc);

  // Despite different internal implementations, they have the same type so they
  // can be stored in the same array (type erasure)
  std::shared_ptr<int> arr[] = {p1, p2};
  return 0;
}  // Each control block extracts its own `del` and `alloc` to perform cleanup
