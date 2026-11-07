// volatile does NOT make an operation atomic.
// ++g_count compiles to load, add, store. Another thread can interleave
// between the load and the store, so this is still a data race.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
volatile int g_count = 0;

void ThreadA() { ++g_count; }
void ThreadB() { ++g_count; }
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
