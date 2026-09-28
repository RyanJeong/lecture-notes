#ifndef MEP_COMMON_ALSA_CAPTURE_HPP_
#define MEP_COMMON_ALSA_CAPTURE_HPP_

#include <alsa/asoundlib.h>

#include <cstdint>

// RAII wrapper over an ALSA capture device, in the same shape as GpioChip:
// the constructor acquires, the destructor releases, and every library call is
// checked. The format is fixed at signed 16-bit little-endian mono because
// that is what both audio labs use, and what the WAV writer expects.
class AlsaCapture {
 public:
  AlsaCapture(const char* device, unsigned int rate, snd_pcm_uframes_t period)
      : pcm_(nullptr), rate_(rate), period_(period), error_(nullptr) {
    int rc = snd_pcm_open(&pcm_, device, SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
      pcm_ = nullptr;
      error_ = snd_strerror(rc);
      return;
    }
    if (!Configure()) {
      snd_pcm_close(pcm_);
      pcm_ = nullptr;
    }
  }

  ~AlsaCapture() {
    if (pcm_ != nullptr) snd_pcm_close(pcm_);
  }

  AlsaCapture(const AlsaCapture&) = delete;
  AlsaCapture& operator=(const AlsaCapture&) = delete;

  bool ok() const { return pcm_ != nullptr; }
  const char* error() const { return error_ != nullptr ? error_ : "no error"; }
  unsigned int rate() const { return rate_; }
  snd_pcm_uframes_t period() const { return period_; }

  // Read exactly `frames` samples into `out`. Returns the frame count, or -1.
  //
  // An overrun (-EPIPE) is not a failure: it means the program was too slow
  // and the driver dropped samples. Recovering and carrying on is the right
  // response -- treating it as fatal would kill the program on any hiccup.
  long Read(std::int16_t* out, snd_pcm_uframes_t frames) {
    if (pcm_ == nullptr) return -1;
    const snd_pcm_sframes_t got = snd_pcm_readi(pcm_, out, frames);
    if (got < 0) {
      const int rc = snd_pcm_recover(pcm_, static_cast<int>(got), 1);
      if (rc < 0) {
        error_ = snd_strerror(rc);
        return -1;
      }
      return 0;  // this period is lost; the next one will be fine
    }
    return static_cast<long>(got);
  }

 private:
  // Hardware parameters are negotiated, not commanded: the driver may return
  // a nearby rate, so the accepted value is read back rather than assumed.
  bool Configure() {
    snd_pcm_hw_params_t* params = nullptr;
    int rc = snd_pcm_hw_params_malloc(&params);
    if (rc < 0) {
      error_ = snd_strerror(rc);
      return false;
    }

    rc = snd_pcm_hw_params_any(pcm_, params);
    if (rc >= 0) {
      rc = snd_pcm_hw_params_set_access(pcm_, params,
                                        SND_PCM_ACCESS_RW_INTERLEAVED);
    }
    if (rc >= 0) {
      rc = snd_pcm_hw_params_set_format(pcm_, params, SND_PCM_FORMAT_S16_LE);
    }
    if (rc >= 0) rc = snd_pcm_hw_params_set_channels(pcm_, params, 1);
    if (rc >= 0) rc = snd_pcm_hw_params_set_rate_near(pcm_, params, &rate_, 0);
    if (rc >= 0) {
      rc = snd_pcm_hw_params_set_period_size_near(pcm_, params, &period_, 0);
    }
    if (rc >= 0) rc = snd_pcm_hw_params(pcm_, params);
    if (rc >= 0) rc = snd_pcm_prepare(pcm_);

    snd_pcm_hw_params_free(params);
    if (rc < 0) {
      error_ = snd_strerror(rc);
      return false;
    }
    return true;
  }

  snd_pcm_t* pcm_;
  unsigned int rate_;
  snd_pcm_uframes_t period_;
  const char* error_;
};

#endif  // MEP_COMMON_ALSA_CAPTURE_HPP_
