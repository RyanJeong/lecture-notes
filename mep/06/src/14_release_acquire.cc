#include <atomic>

// release/acquire: the fix for 11_volatile_no_barrier.cc. Once the consumer
// reads true, every write the producer made before the release store is
// visible, so g_data can stay a plain int without a data race.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int g_data = 0;
std::atomic<bool> g_ready{false};

void Producer() {                                 // core 0
  g_data = 42;                                    // (1)
  g_ready.store(true, std::memory_order_release); // (2)
}

int Consumer() {                                     // core 1
  while (!g_ready.load(std::memory_order_acquire)) { // (3)
    // Spin until the producer publishes the data.
  }
  return g_data; // (4) always 42
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
