#include <atomic>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
std::atomic<bool> g_data_ready{false};

// Producer publishes; release pairs with the consumer's acquire so that
// everything written before the store is visible after the load.
void Producer() { g_data_ready.store(true, std::memory_order_release); }

void Consumer() {
  while (!g_data_ready.load(std::memory_order_acquire)) {
    // Spin until the producer publishes.
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
