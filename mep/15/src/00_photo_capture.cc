#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>

#include "signal_stop.hpp"

namespace {
constexpr const char* kDevice = "/dev/video0";
constexpr const char* kOutPath = "photo.jpg";
constexpr unsigned int kWidth = 640;
constexpr unsigned int kHeight = 480;
constexpr unsigned int kBufferCount = 4;
constexpr int kMaxAttempts = 15;  // frames to try before giving up
void* g_buffers[kBufferCount] = {nullptr};
size_t g_lengths[kBufferCount] = {0};
}  // namespace

// MJPEG, because uncompressed YUYV at 640x480 and 30 fps needs about 18 MB/s,
// most of what a USB 2.0 camera link can carry; MJPEG needs a fraction of it.
bool SetFormat(int fd) {
  v4l2_format format;
  std::memset(&format, 0, sizeof(format));
  format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  format.fmt.pix.width = kWidth;
  format.fmt.pix.height = kHeight;
  format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
  format.fmt.pix.field = V4L2_FIELD_ANY;
  return ::ioctl(fd, VIDIOC_S_FMT, &format) >= 0 &&
         format.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG;
}

// Streaming I/O: the driver owns the buffers, the program maps them once and
// then only hands indices back and forth.
bool MapBuffers(int fd) {
  v4l2_requestbuffers request;
  std::memset(&request, 0, sizeof(request));
  request.count = kBufferCount;
  request.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  request.memory = V4L2_MEMORY_MMAP;
  if (::ioctl(fd, VIDIOC_REQBUFS, &request) < 0 || request.count < 2 ||
      request.count > kBufferCount)
    return false;
  for (unsigned int i = 0; i < request.count; ++i) {
    v4l2_buffer buffer;
    std::memset(&buffer, 0, sizeof(buffer));
    buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffer.memory = V4L2_MEMORY_MMAP;
    buffer.index = i;
    if (::ioctl(fd, VIDIOC_QUERYBUF, &buffer) < 0) return false;
    g_buffers[i] = ::mmap(nullptr, buffer.length, PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, static_cast<off_t>(buffer.m.offset));
    g_lengths[i] = buffer.length;
    if (g_buffers[i] == MAP_FAILED) return false;
    if (::ioctl(fd, VIDIOC_QBUF, &buffer) < 0) return false;
  }
  return true;
}

// Dequeue one filled buffer; the caller must queue it back before the next.
int Grab(int fd, unsigned int* size) {
  v4l2_buffer buffer;
  std::memset(&buffer, 0, sizeof(buffer));
  buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  buffer.memory = V4L2_MEMORY_MMAP;
  if (::ioctl(fd, VIDIOC_DQBUF, &buffer) < 0) return -1;
  *size = buffer.bytesused;
  return static_cast<int>(buffer.index);
}

// Hand a buffer back to the driver so it can be filled again.
bool Requeue(int fd, int index) {
  v4l2_buffer buffer;
  std::memset(&buffer, 0, sizeof(buffer));
  buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  buffer.memory = V4L2_MEMORY_MMAP;
  buffer.index = static_cast<unsigned int>(index);
  return ::ioctl(fd, VIDIOC_QBUF, &buffer) >= 0;
}

// A USB glitch cuts a frame short and the driver still hands it over, with a
// non-zero length. Such a frame saves happily and then opens nowhere, so the
// markers are checked: SOI at the front, EOI at the end.
bool IsCompleteJpeg(const unsigned char* data, unsigned int size) {
  if (data == nullptr || size < 4) return false;
  return data[0] == 0xFF && data[1] == 0xD8 && data[size - 2] == 0xFF &&
         data[size - 1] == 0xD9;
}

// Lab 6-A: warm the sensor up, then save the frame that Ctrl-C lands on.
int main() {
  const int fd = ::open(kDevice, O_RDWR);
  int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  if (fd < 0 || !InstallStopHandler() || !SetFormat(fd) || !MapBuffers(fd) ||
      ::ioctl(fd, VIDIOC_STREAMON, &type) < 0) {
    std::fprintf(stderr, "cannot start %s -- is the webcam plugged in?\n",
                 kDevice);
    return 1;
  }

  // The discarded frames are not waste: a webcam needs a second or two of
  // running exposure and white balance before its output settles.
  std::printf("warming up at %ux%u. Ctrl-C takes the photo\n", kWidth, kHeight);
  long seen = 0;
  unsigned int size = 0;
  int index = -1;
  while (!StopRequested()) {
    index = Grab(fd, &size);
    if (index < 0) break;
    ++seen;
    if (!Requeue(fd, index)) break;
  }

  // Keep grabbing until one frame survives intact: the frame sitting in the
  // queue at the instant Ctrl-C arrives is often a partial one.
  const unsigned char* frame = nullptr;
  for (int attempt = 0; attempt < kMaxAttempts && frame == nullptr; ++attempt) {
    index = Grab(fd, &size);
    if (index < 0) break;
    const unsigned char* candidate =
        static_cast<const unsigned char*>(g_buffers[index]);
    // A rejected buffer must go back, or the queue runs dry after four tries.
    if (IsCompleteJpeg(candidate, size))
      frame = candidate;
    else if (!Requeue(fd, index))
      break;
  }

  int status = 1;
  if (frame != nullptr) {
    std::FILE* file = std::fopen(kOutPath, "wb");
    // Every MJPEG frame is already a complete JPEG, so saving is a byte copy.
    if (file != nullptr && std::fwrite(frame, 1, size, file) == size) {
      status = std::fclose(file) == 0 ? 0 : 1;
      std::printf("\nwrote %s (%u bytes) after %ld warm-up frames\n", kOutPath,
                  size, seen);
    }
  } else {
    std::fprintf(stderr, "\nno intact frame -- check the USB link\n");
  }

  ::ioctl(fd, VIDIOC_STREAMOFF, &type);
  for (unsigned int i = 0; i < kBufferCount; ++i)
    if (g_buffers[i] != nullptr) ::munmap(g_buffers[i], g_lengths[i]);
  ::close(fd);
  return status;
}
