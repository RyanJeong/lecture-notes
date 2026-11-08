// volatile keeps the compiler from reordering the two stores, but a weakly
// ordered CPU such as ARM may make them visible to another core in a
// different order. volatile emits no memory barrier.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
volatile int g_data = 0;
volatile int g_ready = 0;

void Producer() { // core 0
  g_data = 42;
  g_ready = 1;
}

int Consumer() { // core 1
  while (g_ready == 0) {
    // Spin until the producer sets the flag.
  }
  return g_data; // may still read 0
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
