#include <functional>
#include <iostream>
#include <memory>
#include <typeinfo>

// 1. Custom allocator (inherit from std::allocator and add logging)
template <typename T>
class LoggingAllocator : public std::allocator<T> {
 public:
  // [Key Solution] Define the rebind struct
  // Purpose: When the allocator needs to allocate objects of a different type
  // U,
  //          use LoggingAllocator<U> instead of the default allocator<U>
  // Example: If T=int and we need to allocate a control block (different
  // internal type),
  //          the rebind struct tells std::shared_ptr to use
  //          LoggingAllocator<ControlBlock>
  template <typename U>
  struct rebind {
    using other = LoggingAllocator<U>;
  };

  // Constructors are required for type conversion
  // This allows LoggingAllocator<T> to be converted to LoggingAllocator<U>
  LoggingAllocator() = default;

  // Template constructor: enables conversion from LoggingAllocator<U> to
  // LoggingAllocator<T>
  template <typename U>
  LoggingAllocator(const LoggingAllocator<U>&) {}

  T* allocate(size_t n) {
    // Note: n is the number of objects, not the number of bytes
    // For a control block, n is typically 1
    std::cout << "[Allocate] Allocating memory for " << n
              << " object(s) (type: " << typeid(T).name() << ")" << std::endl;
    return std::allocator<T>::allocate(n);
  }

  void deallocate(T* p, size_t n) {
    std::cout << "[Deallocate] Deallocating memory for " << n
              << " object(s) (type: " << typeid(T).name() << ")" << std::endl;
    std::allocator<T>::deallocate(p, n);
  }
};

// 2. Custom deleter
std::function<void(int*)> LoggingDeleter = [](int* p) {
  std::cout << "[Delete] value=" << *p << std::endl;
  delete p;
};

int main() {
  // 3. Create two pointers with different internal configurations

  // p1: uses default allocator + custom deleter
  std::shared_ptr<int> p1(new int(10), LoggingDeleter);

  // p2: uses custom allocator (for control block allocation) + custom deleter
  std::shared_ptr<int> p2(new int(20), LoggingDeleter, LoggingAllocator<int>());

  // 4. [Proof] Despite having different allocators and deleters,
  //    they have the same type (shared_ptr<int>), so they can coexist in an
  //    array
  std::shared_ptr<int> arr[] = {p1, p2};

  return 0;
  // On exit: p2 outputs [Deallocate] log when its control block is destroyed
}