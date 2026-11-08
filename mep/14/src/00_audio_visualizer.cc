#include <alsa/asoundlib.h>

#include <cmath>
#include <cstdint>
#include <cstdio>

#include "signal_stop.hpp"

namespace {
constexpr const char* kDevice = "plughw:1,0";  // default; see `arecord -l`
constexpr unsigned int kRate = 16000;          // enough for speech
constexpr unsigned int kLatencyUs = 100000;    // how much the driver buffers
constexpr snd_pcm_uframes_t kPeriod = 1024;    // ~64 ms per bar update
constexpr int kBarWidth = 50;
constexpr double kFullScale = 32768.0;  // int16_t range
constexpr double kFloorDb = -60.0;      // quieter than this reads as silence
}  // namespace

// Root mean square: the average energy of the block, not its average value.
// A plain average would be near zero for any waveform centred on silence.
double Rms(const std::int16_t* samples, int count) {
  double sum = 0.0;
  for (int i = 0; i < count; ++i)
    sum += static_cast<double>(samples[i]) * static_cast<double>(samples[i]);
  return std::sqrt(sum / static_cast<double>(count));
}

// Hearing is logarithmic, so a linear bar spends most of its length on sounds
// nobody can tell apart. Decibels relative to full scale spread it out.
double RmsToDbfs(double rms) {
  if (rms <= 0.0) return kFloorDb;
  const double db = 20.0 * std::log10(rms / kFullScale);
  return db < kFloorDb ? kFloorDb : db;
}

// Lab 5-A: a level meter drawn in the terminal.
int main(int argc, char* argv[]) {
  const char* device = argc > 1 ? argv[1] : kDevice;
  snd_pcm_t* pcm = nullptr;
  int rc = snd_pcm_open(&pcm, device, SND_PCM_STREAM_CAPTURE, 0);
  if (rc >= 0)
    rc = snd_pcm_set_params(pcm, SND_PCM_FORMAT_S16_LE,
                            SND_PCM_ACCESS_RW_INTERLEAVED, 1, kRate, 1,
                            kLatencyUs);
  if (rc < 0 || !InstallStopHandler()) {
    std::fprintf(stderr, "cannot open %s: %s\n", device, snd_strerror(rc));
    std::fprintf(stderr,
                 "run `arecord -l`, then pass the device, e.g. "
                 "%s plughw:3,0\n",
                 argv[0]);
    return 1;
  }

  std::int16_t samples[kPeriod];
  char bar[kBarWidth + 1];
  std::printf("listening on %s at %u Hz. Ctrl-C to stop\n", device, kRate);
  while (!StopRequested()) {
    const snd_pcm_sframes_t got = snd_pcm_readi(pcm, samples, kPeriod);
    // An overrun means this program was too slow and the driver dropped
    // samples. Recovering is the right answer; dying on a hiccup is not.
    if (got < 0) {
      if (snd_pcm_recover(pcm, static_cast<int>(got), 1) < 0) break;
      continue;
    }
    const double dbfs = RmsToDbfs(Rms(samples, static_cast<int>(got)));
    const int length =
        static_cast<int>((dbfs - kFloorDb) / (0.0 - kFloorDb) * kBarWidth);
    for (int i = 0; i < kBarWidth; ++i) bar[i] = i < length ? '#' : ' ';
    bar[kBarWidth] = '\0';
    std::printf("\r%6.1f dBFS |%s|", dbfs, bar);  // redraw the same line
    std::fflush(stdout);
  }

  std::printf("\nstopped\n");
  return snd_pcm_close(pcm) < 0 ? 1 : 0;
}
