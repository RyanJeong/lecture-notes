#include <cstdio>

#include "signal_stop.hpp"
#include "v4l2_capture.hpp"

namespace {
constexpr const char* kDevice = "/dev/video0";
constexpr const char* kOutPath = "photo.jpg";
constexpr unsigned int kWidth = 640;
constexpr unsigned int kHeight = 480;
constexpr int kMaxAttempts = 15;  // frames to try before giving up
}  // namespace

// The C270 delivers MJPEG, and every MJPEG frame is already a complete JPEG
// file. Saving a still is therefore a byte copy -- no encoding step at all.
bool WriteJpeg(const char* path, const unsigned char* data, unsigned int size) {
  if (data == nullptr || size == 0) return false;
  std::FILE* file = std::fopen(path, "wb");
  if (file == nullptr) return false;
  const bool written = std::fwrite(data, 1, size, file) == size;
  return std::fclose(file) == 0 && written;
}

// A USB glitch cuts a frame short and the driver still hands it over, with a
// non-zero length. Such a frame is saved happily and then opens nowhere, so
// the markers are checked instead of trusted: SOI at the front, EOI at the end.
bool IsCompleteJpeg(const unsigned char* data, unsigned int size) {
  if (data == nullptr || size < 4) return false;
  return data[0] == 0xFF && data[1] == 0xD8 && data[size - 2] == 0xFF &&
         data[size - 1] == 0xD9;
}

// Lab: the program opens the camera and keeps the stream running, then takes
// the picture when Ctrl-C arrives and exits.
//
// The frames thrown away before then are not waste. A webcam needs a second or
// two of running exposure and white balance before its output settles, so a
// still grabbed from a cold start is usually dark and off-colour.
int main() {
  if (!InstallStopHandler()) {
    std::fprintf(stderr, "cannot install the signal handler\n");
    return 1;
  }

  V4l2Capture camera(kDevice, kWidth, kHeight);
  if (!camera.ok()) {
    std::fprintf(stderr, "cannot open %s: %s\n", kDevice, camera.error());
    return 1;
  }
  if (!camera.Start()) {
    std::fprintf(stderr, "cannot start the stream: %s\n", camera.error());
    return 1;
  }

  std::printf("camera warming up at %ux%u. Press Ctrl-C to take the photo\n",
              camera.width(), camera.height());
  std::fflush(stdout);

  long discarded = 0;
  while (!StopRequested()) {
    unsigned int size = 0;
    if (camera.Grab(&size) == nullptr) {
      std::fprintf(stderr, "\ncapture failed: %s\n", camera.error());
      return 1;
    }
    ++discarded;
    if (discarded % 30 == 0) {
      std::printf("\r%ld frames seen, exposure settling", discarded);
      std::fflush(stdout);
    }
  }

  // The signal arrived. Keep grabbing until one frame survives intact: the
  // frame sitting in the queue at that instant is often a partial one.
  const unsigned char* frame = nullptr;
  unsigned int size = 0;
  for (int attempt = 0; attempt < kMaxAttempts && frame == nullptr; ++attempt) {
    const unsigned char* candidate = camera.Grab(&size);
    if (candidate == nullptr) {
      std::fprintf(stderr, "\ncannot grab the final frame: %s\n",
                   camera.error());
      return 1;
    }
    if (IsCompleteJpeg(candidate, size)) frame = candidate;
  }
  if (frame == nullptr) {
    std::fprintf(stderr, "\nno intact frame in %d tries -- check the USB link\n",
                 kMaxAttempts);
    return 1;
  }
  if (!WriteJpeg(kOutPath, frame, size)) {
    std::fprintf(stderr, "\ncannot write %s\n", kOutPath);
    return 1;
  }

  std::printf("\nwrote %s (%u bytes, %ux%u) after %ld warm-up frames\n",
              kOutPath, size, camera.width(), camera.height(), discarded);
  return 0;
}
