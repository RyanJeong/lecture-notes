// volatile does not make a group of updates appear at once. A reader thread
// can observe x updated but y not yet updated, and the unsynchronized access
// is a data race (undefined behavior) even though both variables are volatile.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
volatile int g_x = 0;
volatile int g_y = 0;

void Writer() { // thread A: (0, 0) -> (1, 1)
  g_x = 1;
  g_y = 1;
}

bool Reader() {      // thread B: assumes x == y
  return g_x == g_y; // may be false
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
