void ScaleSamples(const int* raw, float* out, int n) {
  for (int i = 0; i < n; ++i) {
    out[i] = static_cast<float>(raw[i]) * 0.1f;
  }
}
