#include <alsa/asoundlib.h>

#include <cstdint>
#include <cstdio>

#include "signal_stop.hpp"

namespace {
constexpr const char* kDevice = "plughw:1,0";  // default; see `arecord -l`
constexpr const char* kOutPath = "record.wav";
constexpr unsigned int kRate = 16000;
constexpr unsigned int kLatencyUs = 100000;
constexpr snd_pcm_uframes_t kPeriod = 1024;
constexpr std::uint16_t kChannels = 1;
constexpr std::uint16_t kBits = 16;
constexpr std::uint32_t kHeaderBytes = 44;
}  // namespace

// Every multi-byte field in RIFF is little endian, so the bytes go out one at
// a time rather than by writing the integer straight from memory.
bool WriteU16(std::FILE* file, std::uint16_t value) {
  const std::uint8_t bytes[2] = {static_cast<std::uint8_t>(value & 0xFF),
                                 static_cast<std::uint8_t>(value >> 8)};
  return std::fwrite(bytes, 1, 2, file) == 2;
}

bool WriteU32(std::FILE* file, std::uint32_t value) {
  const std::uint8_t bytes[4] = {
      static_cast<std::uint8_t>(value & 0xFF),
      static_cast<std::uint8_t>((value >> 8) & 0xFF),
      static_cast<std::uint8_t>((value >> 16) & 0xFF),
      static_cast<std::uint8_t>(value >> 24)};
  return std::fwrite(bytes, 1, 4, file) == 4;
}

// A 44-byte header followed by the raw samples. Two size fields cannot be
// known until recording stops, so they are written as zero and patched later.
bool WriteHeader(std::FILE* file, std::uint32_t data_bytes) {
  const std::uint16_t align = static_cast<std::uint16_t>(kChannels * kBits / 8);
  return std::fwrite("RIFF", 1, 4, file) == 4 &&
         WriteU32(file, kHeaderBytes - 8 + data_bytes) &&
         std::fwrite("WAVEfmt ", 1, 8, file) == 8 && WriteU32(file, 16) &&
         WriteU16(file, 1) && WriteU16(file, kChannels) &&
         WriteU32(file, kRate) && WriteU32(file, kRate * align) &&
         WriteU16(file, align) && WriteU16(file, kBits) &&
         std::fwrite("data", 1, 4, file) == 4 && WriteU32(file, data_bytes);
}

// Lab 5-B: record until Ctrl-C, then finish the file properly.
int main(int argc, char* argv[]) {
  const char* device = argc > 1 ? argv[1] : kDevice;
  snd_pcm_t* pcm = nullptr;
  int rc = snd_pcm_open(&pcm, device, SND_PCM_STREAM_CAPTURE, 0);
  if (rc >= 0)
    rc = snd_pcm_set_params(pcm, SND_PCM_FORMAT_S16_LE,
                            SND_PCM_ACCESS_RW_INTERLEAVED, kChannels, kRate, 1,
                            kLatencyUs);
  std::FILE* file = std::fopen(kOutPath, "wb");
  if (rc < 0 || file == nullptr || !InstallStopHandler() ||
      !WriteHeader(file, 0)) {
    std::fprintf(stderr, "cannot start on %s: %s\n", device, snd_strerror(rc));
    return 1;
  }

  std::int16_t samples[kPeriod];
  std::uint32_t data_bytes = 0;
  std::printf("recording %s at %u Hz. Ctrl-C to finish\n", kOutPath, kRate);
  while (!StopRequested()) {
    const snd_pcm_sframes_t got = snd_pcm_readi(pcm, samples, kPeriod);
    if (got < 0) {
      if (snd_pcm_recover(pcm, static_cast<int>(got), 1) < 0) break;
      continue;
    }
    const size_t bytes = static_cast<size_t>(got) * sizeof(std::int16_t);
    if (std::fwrite(samples, 1, bytes, file) != bytes) break;
    data_bytes += static_cast<std::uint32_t>(bytes);
    std::printf("\r%.1f s recorded",
                static_cast<double>(data_bytes) / (kRate * 2.0));
    std::fflush(stdout);
  }

  // Ctrl-C is the normal end of this program, so the file must be finished:
  // rewind and patch the two sizes that were left at zero.
  const bool patched =
      std::fseek(file, 0, SEEK_SET) == 0 && WriteHeader(file, data_bytes);
  std::fclose(file);
  snd_pcm_close(pcm);
  std::printf("\nwrote %s (%u bytes)\n", kOutPath, data_bytes + kHeaderBytes);
  return patched ? 0 : 1;
}
