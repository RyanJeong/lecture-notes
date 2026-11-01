#include <cstdint>

// NEON path. The guard keeps the file compilable on an x86 host: the
// intrinsics only exist when the compiler targets arm64 with NEON enabled.
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
// Processes 8 pixels per iteration: 1 de-interleaving load replaces 24 loads,
// and 6 vector multiplies replace 24 scalar multiplies.
void RgbToFloatNeon(const std::uint8_t* src, float* r_out, float* g_out,
                    float* b_out) {
  // v=vector, ld=load, 3=three components, u8=unsigned 8-bit elements.
  // Returns three 8-lane vectors; for RGB, val[0], val[1], val[2] are R,G,B.
  const uint8x8x3_t rgb = vld3_u8(src);

  // v=vector, dup=duplicate, q=128-bit, n=immediate, f32=32-bit float.
  // Broadcast 1/255 to four lanes so each channel can be normalized to [0,1].
  const float32x4_t inv255 = vdupq_n_f32(1.0f / 255.0f);

#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // vmovl: vector move-long (widen); u8 input lanes become u16 without loss.
  const uint16x8_t r16 = vmovl_u8(rgb.val[0]);

  // vget_low_u16 selects four low lanes; vmovl_u16 widens them to u32.
  const uint32x4_t r_low32 = vmovl_u16(vget_low_u16(r16));
  // vcvtq_f32_u32 converts four u32 lanes to a 128-bit vector of f32.
  const float32x4_t r_low = vcvtq_f32_u32(r_low32);
  // vmulq_f32 multiplies four f32 lanes by inv255 for [0,1] normalization.
  const float32x4_t r_low_normalized = vmulq_f32(r_low, inv255);
  // vst1q_f32 stores one 128-bit vector as four contiguous floats.
  vst1q_f32(r_out, r_low_normalized);

  // vget_high_u16 selects four high lanes; vmovl_u16 widens them to u32.
  const uint32x4_t r_high32 = vmovl_u16(vget_high_u16(r16));
  // vcvtq_f32_u32 converts four u32 lanes to f32.
  const float32x4_t r_high = vcvtq_f32_u32(r_high32);
  // vmulq_f32 multiplies four f32 lanes by inv255.
  const float32x4_t r_high_normalized = vmulq_f32(r_high, inv255);
  // vst1q_f32 stores four floats at the upper-half output offset.
  vst1q_f32(r_out + 4, r_high_normalized);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // vmovl_u8 (vector move-long) widens unsigned 8-bit green lanes to u16.
  const uint16x8_t g16 = vmovl_u8(rgb.val[1]);

  // vget_low_u16 selects four low lanes; vmovl_u16 widens them to u32.
  const uint32x4_t g_low32 = vmovl_u16(vget_low_u16(g16));
  // vcvtq_f32_u32 converts four u32 lanes to f32.
  const float32x4_t g_low = vcvtq_f32_u32(g_low32);
  // vmulq_f32 multiplies four f32 lanes by inv255 for [0,1] normalization.
  const float32x4_t g_low_normalized = vmulq_f32(g_low, inv255);
  // vst1q_f32 stores one 128-bit vector as four contiguous floats.
  vst1q_f32(g_out, g_low_normalized);

  // vget_high_u16 selects four high lanes; vmovl_u16 widens them to u32.
  const uint32x4_t g_high32 = vmovl_u16(vget_high_u16(g16));
  // vcvtq_f32_u32 converts four u32 lanes to f32.
  const float32x4_t g_high = vcvtq_f32_u32(g_high32);
  // vmulq_f32 multiplies four f32 lanes by inv255.
  const float32x4_t g_high_normalized = vmulq_f32(g_high, inv255);
  // vst1q_f32 stores the upper four green values at offset four.
  vst1q_f32(g_out + 4, g_high_normalized);
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  // vmovl_u8 (vector move-long) widens unsigned 8-bit blue lanes to u16.
  const uint16x8_t b16 = vmovl_u8(rgb.val[2]);

  // vget_low_u16 selects four low lanes; vmovl_u16 widens them to u32.
  const uint32x4_t b_low32 = vmovl_u16(vget_low_u16(b16));
  // vcvtq_f32_u32 converts four u32 lanes to f32.
  const float32x4_t b_low = vcvtq_f32_u32(b_low32);
  // vmulq_f32 multiplies four f32 lanes by inv255 for [0,1] normalization.
  const float32x4_t b_low_normalized = vmulq_f32(b_low, inv255);
  // vst1q_f32 stores one 128-bit vector as four contiguous floats.
  vst1q_f32(b_out, b_low_normalized);

  // vget_high_u16 selects four high lanes; vmovl_u16 widens them to u32.
  const uint32x4_t b_high32 = vmovl_u16(vget_high_u16(b16));
  // vcvtq_f32_u32 converts four u32 lanes to f32.
  const float32x4_t b_high = vcvtq_f32_u32(b_high32);
  // vmulq_f32 multiplies four f32 lanes by inv255.
  const float32x4_t b_high_normalized = vmulq_f32(b_high, inv255);
  // vst1q_f32 stores the upper four floats at offset four.
  vst1q_f32(b_out + 4, b_high_normalized);
}
#endif  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#endif  // __ARM_NEON
