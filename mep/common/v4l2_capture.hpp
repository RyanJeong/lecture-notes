#ifndef MEP_COMMON_V4L2_CAPTURE_HPP_
#define MEP_COMMON_V4L2_CAPTURE_HPP_

#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>

// RAII wrapper over a V4L2 capture device, fixed to MJPEG because that is what
// the Logitech C270 delivers at full frame rate. Uncompressed YUYV would need
// more USB bandwidth than 640x480 at 30 fps can carry.
//
// Streaming I/O works by handing buffers back and forth with the driver:
// the program queues empty buffers, the driver fills them and hands them back,
// and the program must queue them again or the pipeline stalls.
class V4l2Capture {
 public:
  static const unsigned int kBufferCount = 4;

  V4l2Capture(const char* device, unsigned int width, unsigned int height)
      : fd_(::open(device, O_RDWR)),
        width_(width),
        height_(height),
        buffer_count_(0),
        streaming_(false),
        held_(-1),
        error_(nullptr) {
    for (unsigned int i = 0; i < kBufferCount; ++i) {
      buffers_[i] = nullptr;
      lengths_[i] = 0;
    }
    if (fd_ < 0) {
      error_ = "cannot open the device -- is the webcam plugged in?";
      return;
    }
    if (!CheckCapabilities() || !SetFormat() || !MapBuffers()) Close();
  }

  ~V4l2Capture() { Close(); }

  V4l2Capture(const V4l2Capture&) = delete;
  V4l2Capture& operator=(const V4l2Capture&) = delete;

  bool ok() const { return fd_ >= 0; }
  const char* error() const { return error_ != nullptr ? error_ : "no error"; }
  unsigned int width() const { return width_; }
  unsigned int height() const { return height_; }

  bool Start() {
    if (fd_ < 0 || streaming_) return false;
    for (unsigned int i = 0; i < buffer_count_; ++i) {
      if (!Queue(i)) return false;
    }
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (::ioctl(fd_, VIDIOC_STREAMON, &type) < 0) {
      error_ = "VIDIOC_STREAMON failed";
      return false;
    }
    streaming_ = true;
    return true;
  }

  bool Stop() {
    if (fd_ < 0 || !streaming_) return false;
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    streaming_ = false;
    held_ = -1;
    return ::ioctl(fd_, VIDIOC_STREAMOFF, &type) >= 0;
  }

  // Return one frame. The pointer is into a driver-owned buffer and stays
  // valid only until the next Grab, which is where the previous buffer is
  // handed back. Copy anything that must outlive the call.
  const unsigned char* Grab(unsigned int* size) {
    if (fd_ < 0 || !streaming_ || size == nullptr) return nullptr;
    if (held_ >= 0 && !Queue(static_cast<unsigned int>(held_))) return nullptr;
    held_ = -1;

    v4l2_buffer buf;
    std::memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (::ioctl(fd_, VIDIOC_DQBUF, &buf) < 0) {
      error_ = "VIDIOC_DQBUF failed -- the stream stalled";
      return nullptr;
    }
    held_ = static_cast<int>(buf.index);
    *size = buf.bytesused;
    return static_cast<const unsigned char*>(buffers_[buf.index]);
  }

 private:
  bool CheckCapabilities() {
    v4l2_capability cap;
    std::memset(&cap, 0, sizeof(cap));
    if (::ioctl(fd_, VIDIOC_QUERYCAP, &cap) < 0) {
      error_ = "VIDIOC_QUERYCAP failed -- not a V4L2 device";
      return false;
    }
    const std::uint32_t capabilities =
        (cap.capabilities & V4L2_CAP_DEVICE_CAPS) != 0 ? cap.device_caps
                                                       : cap.capabilities;
    if ((capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0) {
      error_ = "the device cannot capture video";
      return false;
    }
    if ((capabilities & V4L2_CAP_STREAMING) == 0) {
      error_ = "the device does not support streaming I/O";
      return false;
    }
    return true;
  }

  // The driver may hand back a different size than asked for, so the accepted
  // width and height are read back rather than assumed.
  bool SetFormat() {
    v4l2_format fmt;
    std::memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width_;
    fmt.fmt.pix.height = height_;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field = V4L2_FIELD_ANY;
    if (::ioctl(fd_, VIDIOC_S_FMT, &fmt) < 0) {
      error_ = "VIDIOC_S_FMT failed -- MJPEG may not be supported";
      return false;
    }
    if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG) {
      error_ = "the driver refused MJPEG and chose another format";
      return false;
    }
    width_ = fmt.fmt.pix.width;
    height_ = fmt.fmt.pix.height;
    return true;
  }

  bool MapBuffers() {
    v4l2_requestbuffers req;
    std::memset(&req, 0, sizeof(req));
    req.count = kBufferCount;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (::ioctl(fd_, VIDIOC_REQBUFS, &req) < 0) {
      error_ = "VIDIOC_REQBUFS failed";
      return false;
    }
    if (req.count < 2) {
      error_ = "the driver granted too few buffers";
      return false;
    }
    if (req.count > kBufferCount) req.count = kBufferCount;

    for (unsigned int i = 0; i < req.count; ++i) {
      v4l2_buffer buf;
      std::memset(&buf, 0, sizeof(buf));
      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      buf.index = i;
      if (::ioctl(fd_, VIDIOC_QUERYBUF, &buf) < 0) {
        error_ = "VIDIOC_QUERYBUF failed";
        return false;
      }
      void* p = ::mmap(nullptr, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fd_, static_cast<off_t>(buf.m.offset));
      if (p == MAP_FAILED) {
        error_ = "mmap failed";
        return false;
      }
      buffers_[i] = p;
      lengths_[i] = buf.length;
      ++buffer_count_;
    }
    return true;
  }

  bool Queue(unsigned int index) {
    v4l2_buffer buf;
    std::memset(&buf, 0, sizeof(buf));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = index;
    if (::ioctl(fd_, VIDIOC_QBUF, &buf) < 0) {
      error_ = "VIDIOC_QBUF failed";
      return false;
    }
    return true;
  }

  bool Close() {
    if (streaming_) Stop();
    for (unsigned int i = 0; i < buffer_count_; ++i) {
      if (buffers_[i] != nullptr) ::munmap(buffers_[i], lengths_[i]);
      buffers_[i] = nullptr;
    }
    buffer_count_ = 0;
    if (fd_ >= 0) ::close(fd_);
    fd_ = -1;
    return true;
  }

  int fd_;
  unsigned int width_;
  unsigned int height_;
  void* buffers_[kBufferCount];
  size_t lengths_[kBufferCount];
  unsigned int buffer_count_;
  bool streaming_;
  int held_;
  const char* error_;
};

#endif  // MEP_COMMON_V4L2_CAPTURE_HPP_
