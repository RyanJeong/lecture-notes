// Four loops that show what the auto-vectorizer can and cannot transform.
// Check with: clang++ -O2 -mcpu=cortex-a72 -Rpass=loop-vectorize
//             -Rpass-missed=loop-vectorize -c 03_vectorize_report.cc
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Independent iterations: vectorized.
void Scale(float* out, const float* in, float k, int n) {
  for (int i = 0; i < n; ++i) {
    out[i] = in[i] * k;
  }
}

// Each iteration reads the previous result (RAW): not vectorized.
void PrefixSum(float* a, int n) {
  for (int i = 1; i < n; ++i) {
    a[i] = a[i - 1] + a[i];
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Float additions must keep their order: not vectorized without -ffast-math.
float Sum(const float* a, int n) {
  float sum = 0.0f;
  for (int i = 0; i < n; ++i) {
    sum += a[i];
  }
  return sum;
}

// The exit depends on the data, so the trip count is unknown: not vectorized.
int FindZero(const int* a, int n) {
  int i = 0;
  while (i < n && a[i] != 0) {
    ++i;
  }
  return i;
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
