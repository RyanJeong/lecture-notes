#include <cstdint>

// Implementations from 00_rgb_to_float_scalar.cc and 01_rgb_to_float_neon.cc.
void RgbToFloatScalar(const std::uint8_t* src, float* r_out, float* g_out,
                      float* b_out, int count);
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
void RgbToFloatNeon(const std::uint8_t* src, float* r_out, float* g_out,
                    float* b_out);
#endif

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void RgbToFloat(const std::uint8_t* src, float* r, float* g, float* b,
                int count) {
  int i = 0;
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
  // 1. Vectorized main loop: 8 pixels per iteration
  for (; i + 8 <= count; i += 8) {
    RgbToFloatNeon(src + i * 3, r + i, g + i, b + i);
  }
#endif
  // 2. Scalar loop: the remainder on ARM, every pixel on other CPUs
  if (i < count) {
    RgbToFloatScalar(src + i * 3, r + i, g + i, b + i, count - i);
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
