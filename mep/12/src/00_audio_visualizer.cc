#include <cmath>
#include <cstdint>
#include <cstdio>

#include "alsa_capture.hpp"
#include "signal_stop.hpp"

namespace {
// plughw lets ALSA convert if the device cannot do exactly this format; hw
// would refuse instead. Only a default: card numbers follow USB enumeration
// order, so pass the device on the command line when `arecord -l` differs.
constexpr const char* kDevice = "plughw:1,0";
constexpr unsigned int kSampleRate = 16000;  // enough for speech
constexpr snd_pcm_uframes_t kPeriod = 1024;  // ~64 ms per bar update
constexpr int kBarWidth = 50;
constexpr double kFullScale = 32768.0;  // int16_t range
constexpr double kFloorDb = -60.0;      // quieter than this reads as silence
}  // namespace

// Root mean square: the average energy of the block, not its average value.
// A plain average would be near zero for any waveform centred on silence.
double Rms(const std::int16_t* samples, int count) {
  if (samples == nullptr || count <= 0) return 0.0;
  double sum = 0.0;
  for (int i = 0; i < count; ++i) {
    const double value = static_cast<double>(samples[i]);
    sum += value * value;
  }
  return std::sqrt(sum / static_cast<double>(count));
}

// Hearing is logarithmic, so a linear bar spends most of its length on sounds
// nobody can tell apart. Decibels relative to full scale spread it out.
double RmsToDbfs(double rms) {
  if (rms <= 0.0) return kFloorDb;
  const double db = 20.0 * std::log10(rms / kFullScale);
  return db < kFloorDb ? kFloorDb : db;
}

int BarLength(double dbfs, int width) {
  if (width <= 0) return 0;
  const double ratio = (dbfs - kFloorDb) / (0.0 - kFloorDb);  // 0.0 .. 1.0
  int length = static_cast<int>(ratio * width + 0.5);
  if (length < 0) length = 0;
  if (length > width) length = width;
  return length;
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

  std::printf("listening on %s at %u Hz. Ctrl-C to stop\n", device,
              capture.rate());

  std::int16_t samples[kPeriod];
  char bar[kBarWidth + 1];
  while (!StopRequested()) {
    const long frames = capture.Read(samples, kPeriod);
    if (frames < 0) {
      std::fprintf(stderr, "\ncapture failed: %s\n", capture.error());
      return 1;
    }
    if (frames == 0) continue;  // recovered from an overrun

    const double dbfs = RmsToDbfs(Rms(samples, static_cast<int>(frames)));
    const int length = BarLength(dbfs, kBarWidth);
    for (int i = 0; i < kBarWidth; ++i) bar[i] = i < length ? '#' : ' ';
    bar[kBarWidth] = '\0';

    // Carriage return without a newline redraws the same line in place.
    std::printf("\r%6.1f dBFS |%s|", dbfs, bar);
    std::fflush(stdout);
  }

  // Ctrl-C ends the visualiser at once: nothing has been written, so there is
  // nothing to finish. Only the line being redrawn needs closing off.
  std::printf("\nstopped\n");
  return 0;
}
