#include <cstdint>
#include <cstdio>
#include <ctime>
#include <vector>

#include "signal_stop.hpp"
#include "v4l2_capture.hpp"

namespace {
constexpr const char* kDevice = "/dev/video0";
constexpr const char* kOutPath = "record.avi";
constexpr unsigned int kWidth = 640;
constexpr unsigned int kHeight = 480;
constexpr double kNominalFps = 30.0;  // used until the real rate is measured

long NowMillis() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}
}  // namespace

// A minimal AVI writer for MJPEG.
//
// AVI is a RIFF file: nested chunks, each a four-character tag plus a size.
// The catch is that the sizes are not known until recording ends, so they are
// written as zero and patched afterwards -- the same trick as the WAV header,
// one level more nested.
class AviWriter {
 public:
  explicit AviWriter(const char* path)
      : file_(std::fopen(path, "wb")), frames_(0), max_frame_(0) {}

  ~AviWriter() {
    if (file_ != nullptr) std::fclose(file_);
  }

  AviWriter(const AviWriter&) = delete;
  AviWriter& operator=(const AviWriter&) = delete;

  bool ok() const { return file_ != nullptr; }
  long frames() const { return frames_; }

  bool WriteHeader(unsigned int width, unsigned int height) {
    if (file_ == nullptr) return false;
    width_ = width;
    height_ = height;

    if (!Tag("RIFF")) return false;
    riff_size_pos_ = std::ftell(file_);
    if (!U32(0) || !Tag("AVI ")) return false;

    if (!Tag("LIST") || !U32(4 + 8 + 56 + 4 + 8 + 8 + 56 + 8 + 40) ||
        !Tag("hdrl")) {
      return false;
    }

    if (!Tag("avih") || !U32(56)) return false;
    avih_pos_ = std::ftell(file_);
    const std::uint32_t frame_delay =
        static_cast<std::uint32_t>(1000000.0 / kNominalFps);
    if (!U32(frame_delay) ||  // us/frame
        !U32(0) ||            // max bytes per second, patched later
        !U32(0) ||            // padding granularity
        !U32(0x00000010) ||   // AVIF_HASINDEX
        !U32(0) ||            // total frames, patched later
        !U32(0) ||            // initial frames
        !U32(1) ||            // one stream
        !U32(0) ||            // suggested buffer size, patched later
        !U32(width) || !U32(height) || !U32(0) || !U32(0) || !U32(0) ||
        !U32(0)) {
      return false;
    }

    if (!Tag("LIST") || !U32(4 + 8 + 56 + 8 + 40) || !Tag("strl")) return false;

    if (!Tag("strh") || !U32(56)) return false;
    strh_pos_ = std::ftell(file_);
    if (!Tag("vids") || !Tag("MJPG") || !U32(0) ||        // flags
        !U16(0) || !U16(0) ||                             // priority, language
        !U32(0) ||                                        // initial frames
        !U32(1) ||                                        // scale
        !U32(static_cast<std::uint32_t>(kNominalFps)) ||  // rate, patched later
        !U32(0) ||                                        // start
        !U32(0) ||            // length in frames, patched later
        !U32(0) ||            // suggested buffer size, patched later
        !U32(0xFFFFFFFFu) ||  // quality: default
        !U32(0) ||            // sample size: variable
        !U16(0) || !U16(0) || !U16(static_cast<std::uint16_t>(width)) ||
        !U16(static_cast<std::uint16_t>(height))) {
      return false;
    }

    if (!Tag("strf") || !U32(40)) return false;
    if (!U32(40) || !U32(width) || !U32(height) || !U16(1) || !U16(24) ||
        !Tag("MJPG") || !U32(width * height * 3) || !U32(0) || !U32(0) ||
        !U32(0) || !U32(0)) {
      return false;
    }

    if (!Tag("LIST")) return false;
    movi_size_pos_ = std::ftell(file_);
    if (!U32(0) || !Tag("movi")) return false;
    movi_start_ = std::ftell(file_);  // just past the "movi" tag
    return true;
  }

  // Every chunk must start on an even offset, so an odd-length frame gets one
  // padding byte that is not counted in the chunk size.
  bool WriteFrame(const unsigned char* data, unsigned int size) {
    if (file_ == nullptr || data == nullptr || size == 0) return false;
    const long pos = std::ftell(file_);
    if (!Tag("00dc") || !U32(size)) return false;
    if (std::fwrite(data, 1, size, file_) != size) return false;
    if ((size % 2) != 0) {
      const unsigned char pad = 0;
      if (std::fwrite(&pad, 1, 1, file_) != 1) return false;
    }
    // Offsets in the index are relative to the "movi" tag itself, which is
    // four bytes before the first chunk.
    index_.push_back(static_cast<std::uint32_t>(pos - movi_start_ + 4));
    sizes_.push_back(size);
    if (size > max_frame_) max_frame_ = size;
    ++frames_;
    return true;
  }

  // Append the index, then go back and fill in every size left at zero.
  bool Finalise(double seconds) {
    if (file_ == nullptr || frames_ == 0) return false;
    const long movi_end = std::ftell(file_);

    if (!Tag("idx1") || !U32(static_cast<std::uint32_t>(frames_) * 16)) {
      return false;
    }
    for (long i = 0; i < frames_; ++i) {
      if (!Tag("00dc") || !U32(0x00000010) ||  // AVIIF_KEYFRAME
          !U32(index_[static_cast<size_t>(i)]) ||
          !U32(sizes_[static_cast<size_t>(i)])) {
        return false;
      }
    }
    const long file_end = std::ftell(file_);

    // Measured, not assumed: if the camera delivered 24 fps the file must say
    // 24, otherwise playback runs at the wrong speed.
    const double fps =
        seconds > 0.0 ? static_cast<double>(frames_) / seconds : kNominalFps;
    const std::uint32_t us_per_frame =
        static_cast<std::uint32_t>(1000000.0 / (fps > 0.0 ? fps : 1.0));

    return Patch(riff_size_pos_, static_cast<std::uint32_t>(file_end - 8)) &&
           Patch(movi_size_pos_,
                 static_cast<std::uint32_t>(movi_end - movi_start_ + 4)) &&
           Patch(avih_pos_, us_per_frame) &&
           Patch(avih_pos_ + 16, static_cast<std::uint32_t>(frames_)) &&
           Patch(avih_pos_ + 28, max_frame_) &&
           Patch(strh_pos_ + 32, static_cast<std::uint32_t>(fps + 0.5)) &&
           Patch(strh_pos_ + 40, static_cast<std::uint32_t>(frames_)) &&
           Patch(strh_pos_ + 44, max_frame_);
  }

 private:
  bool Tag(const char* four) { return std::fwrite(four, 1, 4, file_) == 4; }

  bool U32(std::uint32_t v) {
    const unsigned char b[4] = {static_cast<unsigned char>(v & 0xFF),
                                static_cast<unsigned char>((v >> 8) & 0xFF),
                                static_cast<unsigned char>((v >> 16) & 0xFF),
                                static_cast<unsigned char>((v >> 24) & 0xFF)};
    return std::fwrite(b, 1, 4, file_) == 4;
  }

  bool U16(std::uint16_t v) {
    const unsigned char b[2] = {static_cast<unsigned char>(v & 0xFF),
                                static_cast<unsigned char>((v >> 8) & 0xFF)};
    return std::fwrite(b, 1, 2, file_) == 2;
  }

  bool Patch(long position, std::uint32_t value) {
    return std::fseek(file_, position, SEEK_SET) == 0 && U32(value);
  }

  std::FILE* file_;
  long frames_;
  std::uint32_t max_frame_;
  unsigned int width_ = 0;
  unsigned int height_ = 0;
  long riff_size_pos_ = 0;
  long avih_pos_ = 0;
  long strh_pos_ = 0;
  long movi_size_pos_ = 0;
  long movi_start_ = 0;
  std::vector<std::uint32_t> index_;
  std::vector<std::uint32_t> sizes_;
};

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

  AviWriter avi(kOutPath);
  if (!avi.ok() || !avi.WriteHeader(camera.width(), camera.height())) {
    std::fprintf(stderr, "cannot create %s\n", kOutPath);
    return 1;
  }
  if (!camera.Start()) {
    std::fprintf(stderr, "cannot start the stream: %s\n", camera.error());
    return 1;
  }

  std::printf("recording %s at %ux%u MJPEG. Ctrl-C to finish\n", kOutPath,
              camera.width(), camera.height());
  std::fflush(stdout);

  const long started = NowMillis();
  while (!StopRequested()) {
    unsigned int size = 0;
    const unsigned char* frame = camera.Grab(&size);
    if (frame == nullptr) {
      std::fprintf(stderr, "\ncapture failed: %s\n", camera.error());
      return 1;
    }
    if (!avi.WriteFrame(frame, size)) {
      std::fprintf(stderr, "\nwrite failed -- out of disk space?\n");
      return 1;
    }
    if (avi.frames() % 15 == 0) {
      std::printf("\r%ld frames, %.1f s", avi.frames(),
                  static_cast<double>(NowMillis() - started) / 1000.0);
      std::fflush(stdout);
    }
  }

  const double seconds = static_cast<double>(NowMillis() - started) / 1000.0;
  if (!camera.Stop()) {
    std::fprintf(stderr, "\ncannot stop the stream: %s\n", camera.error());
    return 1;
  }

  // Ctrl-C is the normal end of a recording, so the index and every size
  // field still have to be written. Skipping this leaves an unplayable file.
  if (!avi.Finalise(seconds)) {
    std::fprintf(stderr, "\ncannot finalise %s -- the file is unplayable\n",
                 kOutPath);
    return 1;
  }

  const double fps =
      seconds > 0.0 ? static_cast<double>(avi.frames()) / seconds : 0.0;
  std::printf("\nwrote %s: %ld frames in %.1f s (%.1f fps)\n", kOutPath,
              avi.frames(), seconds, fps);
  return 0;
}
