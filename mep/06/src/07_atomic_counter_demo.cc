#include <atomic>
#include <cstdio>
#include <thread>

const int kThreadCount = 4;
const int kIncrementsPerThread = 500000;

void Increment(std::atomic<int>* counter) {
  for (int index = 0; index < kIncrementsPerThread; ++index) ++(*counter);
}

int main() {
  std::atomic<int> counter{0};
  std::thread workers[kThreadCount];
  for (int index = 0; index < kThreadCount; ++index)
    workers[index] = std::thread(Increment, &counter);
  for (auto& worker : workers) worker.join();

  const int expected = kThreadCount * kIncrementsPerThread;
  const int actual = counter.load();
  std::printf("expected=%d actual=%d\n", expected, actual);
  return actual == expected ? 0 : 1;
}
