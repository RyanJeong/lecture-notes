# syntax=docker/dockerfile:1
FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

# The toolchain and CMake only. The image pins the build environment, so the
# same command produces the same binary on any host and in CI.
RUN apt-get update && apt-get install -y --no-install-recommends \
  cmake \
  file \
  g++-aarch64-linux-gnu \
  make && rm -rf /var/lib/apt/lists/*

WORKDIR /src

CMD cmake -S /src -B /out \
  -DCMAKE_TOOLCHAIN_FILE=/src/cmake/toolchains/aarch64-linux-gnu.cmake \
  -DCMAKE_BUILD_TYPE=Release &&
  cmake --build /out --parallel
