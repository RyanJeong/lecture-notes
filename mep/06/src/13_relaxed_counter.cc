#include <atomic>

// relaxed: only the counter itself must be exact. No other data depends on
// its value, so no ordering with other memory accesses is required.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
std::atomic<int> g_packets{0};

void OnPacket() { // called by many threads
  g_packets.fetch_add(1, std::memory_order_relaxed);
}

int Report() { // called after all threads are joined
  return g_packets.load(std::memory_order_relaxed);
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
