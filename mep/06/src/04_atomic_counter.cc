#include <atomic>

// std::atomic guarantees both atomicity and the memory ordering that
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// volatile alone cannot provide.
std::atomic<int> g_count{0};

void ThreadA() { ++g_count; }
void ThreadB() { ++g_count; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
