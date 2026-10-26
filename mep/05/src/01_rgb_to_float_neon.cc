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
  const uint8x8x3_t rgb = vld3_u8(src);
  const float32x4_t inv255 = vdupq_n_f32(1.0f / 255.0f);

  const uint16x8_t r16 = vmovl_u8(rgb.val[0]);
  vst1q_f32(r_out,
            vmulq_f32(vcvtq_f32_u32(vmovl_u16(vget_low_u16(r16))), inv255));
  vst1q_f32(r_out + 4,
            vmulq_f32(vcvtq_f32_u32(vmovl_u16(vget_high_u16(r16))), inv255));

  /* continues on next slide */
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */

#if 1 /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
  /* continued from previous slide */

  const uint16x8_t g16 = vmovl_u8(rgb.val[1]);
  vst1q_f32(g_out,
            vmulq_f32(vcvtq_f32_u32(vmovl_u16(vget_low_u16(g16))), inv255));
  vst1q_f32(g_out + 4,
            vmulq_f32(vcvtq_f32_u32(vmovl_u16(vget_high_u16(g16))), inv255));

  const uint16x8_t b16 = vmovl_u8(rgb.val[2]);
  vst1q_f32(b_out,
            vmulq_f32(vcvtq_f32_u32(vmovl_u16(vget_low_u16(b16))), inv255));
  vst1q_f32(b_out + 4,
            vmulq_f32(vcvtq_f32_u32(vmovl_u16(vget_high_u16(b16))), inv255));
}
#endif  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
#endif  // __ARM_NEON
