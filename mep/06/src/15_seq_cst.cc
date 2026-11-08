#include <atomic>

// seq_cst: each thread stores its own flag and then loads the other's.
// With release/acquire the store may become visible after the load, so both
// threads can read false. seq_cst puts all four operations in one total order,
// so at least one thread sees the other's flag.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
std::atomic<bool> g_a_wants{false};
std::atomic<bool> g_b_wants{false};

bool ThreadA() { // true: A enters the critical section
  g_a_wants.store(true);
  return !g_b_wants.load();
}

bool ThreadB() { // true: B enters the critical section
  g_b_wants.store(true);
  return !g_a_wants.load();
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
