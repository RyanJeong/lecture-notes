#ifndef MEP_LAB04_HTTP_HPP_
#define MEP_LAB04_HTTP_HPP_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

// The smallest HTTP server that a browser will talk to: one request, one
// response, connection closed. No keep-alive, no concurrency.
class Http {
 public:
  explicit Http(int port) : listener_(::socket(AF_INET, SOCK_STREAM, 0)) {
    if (listener_ < 0) return;
    const int one = 1;
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(static_cast<std::uint16_t>(port));
    if (::setsockopt(listener_, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) <
            0 ||
        ::bind(listener_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) <
            0 ||
        ::listen(listener_, 4) < 0) {
      ::close(listener_);
      listener_ = -1;
    }
  }

  ~Http() {
    if (listener_ >= 0) ::close(listener_);
  }

  Http(const Http&) = delete;
  Http& operator=(const Http&) = delete;

  bool ok() const { return listener_ >= 0; }

  // Waits up to timeout_ms so the caller can re-check its stop flag while no
  // browser is asking for anything. Returns -1 when nothing arrived.
  int Accept(int timeout_ms) const {
    pollfd descriptor;
    descriptor.fd = listener_;
    descriptor.events = POLLIN;
    descriptor.revents = 0;
    if (::poll(&descriptor, 1, timeout_ms) <= 0) return -1;
    if ((descriptor.revents & POLLIN) == 0) return -1;
    return ::accept(listener_, nullptr, nullptr);
  }

  // True when the request line asks for `path`.
  static bool Wants(int client, const char* path) {
    char request[512];
    const ssize_t got = ::read(client, request, sizeof(request) - 1);
    if (got <= 0) return false;
    request[got] = '\0';
    return std::strstr(request, path) != nullptr;
  }

  static bool Send(int client, const char* type, const char* body, int length) {
    char head[160];
    const int head_len = std::snprintf(
        head, sizeof(head),
        "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n"
        "Connection: close\r\n\r\n",
        type, length);
    if (head_len < 0 || static_cast<size_t>(head_len) >= sizeof(head))
      return false;
    return SendAll(client, head, static_cast<size_t>(head_len)) &&
           SendAll(client, body, static_cast<size_t>(length));
  }

 private:
  // write() may accept fewer bytes than asked, so the loop is not optional.
  static bool SendAll(int fd, const char* data, size_t size) {
    size_t sent = 0;
    while (sent < size) {
      const ssize_t n = ::write(fd, data + sent, size - sent);
      if (n <= 0) return false;
      sent += static_cast<size_t>(n);
    }
    return true;
  }

  int listener_;
};

// A page small enough to embed: it just polls the JSON endpoint and redraws.
const char* const kDashboard =
    "<!doctype html><meta charset=utf-8><title>MEP Sensor Hub</title>"
    "<style>body{font-family:sans-serif;margin:2rem}"
    "td{padding:.4rem 1rem;border-bottom:1px solid #ddd}"
    ".bad{color:#c0392b}</style>"
    "<h1>Sensor Hub</h1><table id=t></table>"
    "<script>setInterval(async()=>{"
    "const r=await(await fetch('/api')).json();"
    "document.getElementById('t').innerHTML=r.sensors.map(s=>"
    "`<tr><td>${s.name}</td><td class=${s.ok?'':'bad'}>"
    "${s.ok?s.value.toFixed(2)+' '+s.unit:'--'}</td></tr>`).join('');"
    "},1000)</script>";

#endif  // MEP_LAB04_HTTP_HPP_
