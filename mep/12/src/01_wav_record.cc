#include <cstdint>
#include <cstdio>
#include <cstring>

#include "alsa_capture.hpp"
#include "signal_stop.hpp"

namespace {
constexpr const char* kDevice = "plughw:1,0";
constexpr const char* kOutPath = "record.wav";
constexpr unsigned int kSampleRate = 16000;
constexpr snd_pcm_uframes_t kPeriod = 1024;
constexpr std::uint16_t kChannels = 1;
constexpr std::uint16_t kBitsPerSample = 16;
constexpr std::uint16_t kPcmFormat = 1;  // 1 means uncompressed PCM
constexpr long kHeaderBytes = 44;
}  // namespace

// A WAV file is a RIFF container: a 44-byte header followed by raw samples.
// Every multi-byte field is little-endian, which is why they are written byte
// by byte instead of memcpy-ing the host's integers.
bool WriteU32(std::FILE* file, std::uint32_t value) {
  const unsigned char bytes[4] = {
      static_cast<unsigned char>(value & 0xFF),
      static_cast<unsigned char>((value >> 8) & 0xFF),
      static_cast<unsigned char>((value >> 16) & 0xFF),
      static_cast<unsigned char>((value >> 24) & 0xFF)};
  return std::fwrite(bytes, 1, 4, file) == 4;
}

bool WriteU16(std::FILE* file, std::uint16_t value) {
  const unsigned char bytes[2] = {
      static_cast<unsigned char>(value & 0xFF),
      static_cast<unsigned char>((value >> 8) & 0xFF)};
  return std::fwrite(bytes, 1, 2, file) == 2;
}

// The two size fields are unknown while recording, so they are written as
// zero now and patched in once the total is known. This is why an interrupted
// recorder leaves a file that players reject: the sizes still say zero.
bool WriteWavHeader(std::FILE* file, unsigned int rate,
                    std::uint32_t data_bytes) {
  const std::uint32_t byte_rate =
      rate * kChannels * (kBitsPerSample / 8);
  const std::uint16_t block_align =
      static_cast<std::uint16_t>(kChannels * (kBitsPerSample / 8));
  return std::fwrite("RIFF", 1, 4, file) == 4 &&
         WriteU32(file, 36 + data_bytes) &&
         std::fwrite("WAVEfmt ", 1, 8, file) == 8 &&
         WriteU32(file, 16) &&              // fmt chunk size
         WriteU16(file, kPcmFormat) &&
         WriteU16(file, kChannels) &&
         WriteU32(file, rate) &&
         WriteU32(file, byte_rate) &&
         WriteU16(file, block_align) &&
         WriteU16(file, kBitsPerSample) &&
         std::fwrite("data", 1, 4, file) == 4 &&
         WriteU32(file, data_bytes);
}

int main(int argc, char* argv[]) {
  if (!InstallStopHandler()) {
    std::fprintf(stderr, "cannot install the signal handler\n");
    return 1;
  }

  const char* device = argc > 1 ? argv[1] : kDevice;
  AlsaCapture capture(device, kSampleRate, kPeriod);
  if (!capture.ok()) {
    std::fprintf(stderr, "cannot open %s: %s\n", device, capture.error());
    std::fprintf(stderr, "run `arecord -l`, then pass the device, e.g. "
                         "%s plughw:3,0\n", argv[0]);
    return 1;
  }

  std::FILE* file = std::fopen(kOutPath, "wb");
  if (file == nullptr) {
    std::fprintf(stderr, "cannot create %s\n", kOutPath);
    return 1;
  }
  if (!WriteWavHeader(file, capture.rate(), 0)) {
    std::fprintf(stderr, "cannot write the WAV header\n");
    std::fclose(file);
    return 1;
  }

  std::printf("recording %s at %u Hz, %u-bit mono. Ctrl-C to finish\n",
              kOutPath, capture.rate(), kBitsPerSample);

  std::int16_t samples[kPeriod];
  std::uint32_t data_bytes = 0;
  while (!StopRequested()) {
    const long frames = capture.Read(samples, kPeriod);
    if (frames < 0) {
      std::fprintf(stderr, "\ncapture failed: %s\n", capture.error());
      std::fclose(file);
      return 1;
    }
    if (frames == 0) continue;

    const size_t bytes = static_cast<size_t>(frames) * sizeof(std::int16_t);
    if (std::fwrite(samples, 1, bytes, file) != bytes) {
      std::fprintf(stderr, "\nwrite failed -- out of disk space?\n");
      std::fclose(file);
      return 1;
    }
    data_bytes += static_cast<std::uint32_t>(bytes);

    const double seconds =
        static_cast<double>(data_bytes) /
        static_cast<double>(capture.rate() * kChannels * (kBitsPerSample / 8));
    std::printf("\r%.1f s recorded", seconds);
    std::fflush(stdout);
  }

  // Ctrl-C is the normal end of this program, not an error, so the file must
  // be finished properly: rewind and patch the two sizes left at zero.
  if (std::fseek(file, 0, SEEK_SET) != 0 ||
      !WriteWavHeader(file, capture.rate(), data_bytes)) {
    std::fprintf(stderr, "\ncannot finalise the header -- %s is unplayable\n",
                 kOutPath);
    std::fclose(file);
    return 1;
  }
  std::fclose(file);

  std::printf("\nwrote %s (%ld bytes, %.1f s)\n", kOutPath,
              static_cast<long>(data_bytes) + kHeaderBytes,
              static_cast<double>(data_bytes) /
                  static_cast<double>(capture.rate() * kChannels *
                                      (kBitsPerSample / 8)));
  return 0;
}
