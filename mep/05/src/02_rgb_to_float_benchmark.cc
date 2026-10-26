#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
void RgbToFloatScalar(const std::uint8_t* src, float* r_out, float* g_out,
                      float* b_out, int count);
void RgbToFloatNeon(const std::uint8_t* src, float* r_out, float* g_out,
                    float* b_out);

namespace {

const int kPixelCount = 1920 * 1080 + 3;
const int kSampleCount = 9;
const int kPixelsPerNeonCall = 8;

struct Channels {
  std::vector<float> red;
  std::vector<float> green;
  std::vector<float> blue;
};

typedef void (*Converter)(const std::uint8_t*, float*, float*, float*, int);

void ConvertScalar(const std::uint8_t* src, float* red, float* green,
                   float* blue, int count) {
  RgbToFloatScalar(src, red, green, blue, count);
}

void ConvertNeon(const std::uint8_t* src, float* red, float* green,
                 float* blue, int count) {
  int index = 0;
  for (; index + kPixelsPerNeonCall <= count;
       index += kPixelsPerNeonCall) {
    RgbToFloatNeon(src + index * 3, red + index, green + index, blue + index);
  }
  if (index < count) {
    RgbToFloatScalar(src + index * 3, red + index, green + index, blue + index,
                     count - index);
  }
}

Channels MakeChannels(int count) {
  Channels channels;
  channels.red.resize(count);
  channels.green.resize(count);
  channels.blue.resize(count);
  return channels;
}

double MeasureMilliseconds(Converter convert, const std::vector<std::uint8_t>& src,
                           Channels* channels) {
  const std::chrono::steady_clock::time_point start =
      std::chrono::steady_clock::now();
  convert(src.data(), channels->red.data(), channels->green.data(),
          channels->blue.data(), kPixelCount);
  const std::chrono::steady_clock::time_point finish =
      std::chrono::steady_clock::now();
  return std::chrono::duration<double, std::milli>(finish - start).count();
}

double Checksum(const Channels& channels) {
  double sum = 0.0;
  for (int index = 0; index < kPixelCount; ++index) {
    sum += channels.red[index] + channels.green[index] + channels.blue[index];
  }
  return sum;
}

double Median(std::vector<double> samples) {
  std::sort(samples.begin(), samples.end());
  return samples[samples.size() / 2];
}

}  // namespace

int main() {
  std::vector<std::uint8_t> src(kPixelCount * 3);
  for (int index = 0; index < static_cast<int>(src.size()); ++index) {
    src[index] = static_cast<std::uint8_t>((index * 37 + index / 3) & 0xff);
  }

  Channels scalar = MakeChannels(kPixelCount);
  Channels neon = MakeChannels(kPixelCount);
  ConvertScalar(src.data(), scalar.red.data(), scalar.green.data(),
                scalar.blue.data(), kPixelCount);
  ConvertNeon(src.data(), neon.red.data(), neon.green.data(), neon.blue.data(),
              kPixelCount);

  for (int index = 0; index < kPixelCount; ++index) {
    if (std::fabs(scalar.red[index] - neon.red[index]) > 1e-6f ||
        std::fabs(scalar.green[index] - neon.green[index]) > 1e-6f ||
        std::fabs(scalar.blue[index] - neon.blue[index]) > 1e-6f) {
      std::fprintf(stderr, "Output mismatch at pixel %d\n", index);
      return 1;
    }
  }

  std::vector<double> scalar_samples;
  std::vector<double> neon_samples;
  for (int sample = 0; sample < kSampleCount; ++sample) {
    if (sample % 2 == 0) {
      scalar_samples.push_back(
          MeasureMilliseconds(ConvertScalar, src, &scalar));
      neon_samples.push_back(MeasureMilliseconds(ConvertNeon, src, &neon));
    } else {
      neon_samples.push_back(MeasureMilliseconds(ConvertNeon, src, &neon));
      scalar_samples.push_back(
          MeasureMilliseconds(ConvertScalar, src, &scalar));
    }
  }

  const double scalar_median = Median(scalar_samples);
  const double neon_median = Median(neon_samples);
  std::printf("pixels=%d samples=%d\n", kPixelCount, kSampleCount);
  std::printf("scalar median: %.3f ms\n", scalar_median);
  std::printf("NEON median:   %.3f ms\n", neon_median);
  std::printf("speedup:       %.2fx\n", scalar_median / neon_median);
  std::printf("checksum:      %.3f\n", Checksum(neon));
  return 0;
}
#else
int main() {
  std::fprintf(stderr, "This benchmark requires an ARM NEON target.\n");
  return 1;
}
#endif
