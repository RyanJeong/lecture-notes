#include <cstdint>

// Scalar reference: convert 8 packed RGB uint8 pixels to normalized floats.
// 8 pixels cost 24 loads, 24 int-to-float conversions and 24 multiplies.
#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
void RgbToFloatScalar(const std::uint8_t* src, float* r_out, float* g_out,
                      float* b_out, int count) {
  const float inv255 = 1.0f / 255.0f;
  for (int i = 0; i < count; ++i) {
    r_out[i] = static_cast<float>(src[i * 3 + 0]) * inv255;
    g_out[i] = static_cast<float>(src[i * 3 + 1]) * inv255;
    b_out[i] = static_cast<float>(src[i * 3 + 2]) * inv255;
  }
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
