<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 1 - 크로스 컴파일

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 1 - 목표 (Goals)

- **핵심 목표**: 호스트 PC 환경에서 타깃 보드(라즈베리파이)용 **64비트 ARM(arm64) 바이너리** 교차 빌드 및 검증

### 실습 환경 및 준비 사항

| 구분 | 요구 환경 및 상세 내용 |
| :--- | :--------------------- |
| **호스트 PC** | x86_64 리눅스 환경(또는 Docker 구동 가능 환경) |
| **타깃 보드** | 동일 로컬 네트워크에 연결된 라즈베리파이(Raspberry Pi OS 64-bit) |
| **확인 정보** | 타깃 보드의 IP 주소 및 SSH 로그인 계정/비밀번호 |

---

## 실습 1 - 구성 (Layout)

```text
mep/lab01/
├── CMakeLists.txt                         # build description
├── Dockerfile                             # pinned build environment
├── cmake/
│   └── toolchains/
│       └── aarch64-linux-gnu.cmake        # which compiler to use
└── src/
    └── helloworld.cc                      # no libraries at all
```

---

## 실습 1 - 예제 코드 (Example)

[//]: # "INCLUDE: ./mep/10/src/helloworld.cc"

- **포인터 크기 검증**: `sizeof(void*)` 결과가 **8바이트**로 출력되어야 64비트 타깃 아키텍처(arm64)로 정상 빌드된 상태
- **바이너리 검증**: 빌드 직후 `file` 명령어를 통해 타깃 아키텍처 일치 여부 필수 확인

---

## 실습 1 - 방법 A: 툴체인 직접 사용 (Toolchain)

```bash
# On the HOST -- install the cross toolchain once
sudo apt install -y g++-aarch64-linux-gnu
aarch64-linux-gnu-g++ --version

cd mep/lab01
aarch64-linux-gnu-g++ -std=c++14 -Wall -Wextra \
        src/helloworld.cc -o hello_pi
```

- **크로스 컴파일러 접두사**: `aarch64-linux-gnu-` 접두사(Prefix)가 부여된 타깃 전용 툴체인 호출
- **네이티브 빌드 주의**: 일반 `g++` 호출 시 호스트용(x86_64) 바이너리가 생성되어 타깃 실행 불가

---

## 실습 1 - 아키텍처 확인 (Verify the Target)

- **빈번한 실수**: 호스트용으로 네이티브 빌드된 결과물을 타깃 보드로 복사하여 실행을 시도하는 경우

```bash
file hello_pi
# ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), ...
```

| 출력 문자열 | 의미 및 판정 결과 |
| :--- | :--- |
| `ARM aarch64` | **타깃 바이너리**: 라즈베리파이 64비트 환경 전용으로 정상 생성 |
| `x86-64` | **호스트 바이너리**: 크로스 컴파일이 아닌 네이티브 빌드가 수행된 상태 |
| `dynamically linked` | **동적 링크**: 타깃 런타임에 일치하는 공유 라이브러리(`.so`) 존재 필요 |
| `statically linked` | **정적 링크**: 외부 의존성 없이 독립 실행 가능 |

- **오류 증상**: 아키텍처 불일치 시 타깃에서 `cannot execute binary file: Exec format error` 발생

---

## 실습 1 - 방법 B: CMake 툴체인 파일 (Toolchain File) 사용

[//]: # "INCLUDE: ./mep/10/cmake/toolchains/aarch64-linux-gnu.cmake"

---

## 실습 1 - 방법 B: CMake 툴체인 파일 (Toolchain File) 사용 (Cont'd)

[//]: # "INCLUDE: ./mep/10/CMakeLists.txt"

```bash
# Configure the build directory with the cross-toolchain file
cmake -B build-pi \
    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/aarch64-linux-gnu.cmake \
    -DCMAKE_BUILD_TYPE=Release

# Build the target binary and inspect its architecture
cmake --build build-pi -j
file build-pi/hello_pi
```

---

## 실습 1 - 방법 C: 도커 (Pinned Environment)

- **빌드 환경 고정**: 도커(Docker) 컨테이너 내부에 툴체인 및 빌드 도구를 패키징하여 환경 격리
- **빌드 재현성 보장**: 호스트 OS 설정 차이와 무관하게 동일한 빌드 결과물 도출

[//]: # "INCLUDE: ./mep/10/Dockerfile"

---

## 실습 1 - 방법 C: 도커 빌드 (Building in a Container)

```bash
cd mep/lab01

docker build -t mep-lab01 .

# Mount the source read-only, write the build output to ./out
docker run --rm \
  -v "$PWD":/src:ro \
  -v "$PWD/out":/out \
  mep-lab01

file out/hello_pi
```

- **소스 트리 보호**: 소스 디렉터리를 **읽기 전용**(`:ro`)으로 바인드 마운트하여 컨테이너에 의한 호스트 파일 변경 방지
- **CI/CD 파이프라인 연계**: 로컬에서 검증된 도커 이미지를 GitHub Actions 등 자동화 빌드 환경에 그대로 재사용 가능

---

## 실습 1 - 전송과 실행 (Transfer and Run)

```bash
# 1. Find the target's address (run on the Pi, or check the router)
hostname -I                     # e.g. 192.168.0.42

# 2. Copy the binary from the host to the Pi
scp hello_pi <user>@192.168.0.42:~/
#      ^ source        ^ destination

# 3. Log in and run it on the target
ssh <user>@192.168.0.42
chmod +x hello_pi               # restore the executable bit if needed
./hello_pi
# Hello, World!
# pointer size: 8 bytes
```

- **SCP 파일 복사**: `scp <로컬 파일> <사용자>@<주소>:<원격 경로>` 형식으로 타깃 보드에 파일 배포
- **SSH 키 기반 인증**: `ssh-copy-id <사용자>@<주소>`로 공개키를 등록하면 이후 비밀번호 입력 과정 생략 가능

---

## 실습 1 - 한 줄로 잇기 (One-Liner)

- **반복 검증 자동화**: 빌드 ➔ 파일 전송 ➔ 타깃 실행 단계를 단일 명령어로 결합하여 개발 생산성 향상

```bash
# Build, transfer, and execute on the target in a single pipeline
aarch64-linux-gnu-g++ -std=c++14 src/helloworld.cc -o hello_pi \
  && scp hello_pi <user>@192.168.0.42:~/ \
  && ssh <user>@192.168.0.42 './hello_pi'
```

- **조건부 연계(`&&`)**: 앞선 단계가 정상 종료(종료 코드 0)된 경우에만 다음 명령을 실행하며, 오류 발생 시 즉시 중단

---

## 실습 1 - 과제 (Tasks)

1. **방법 A(툴체인 직접 사용)**: 바이너리 빌드 후 `file` 명령어로 `ARM aarch64` 아키텍처 확인
2. **타깃 실행 및 검증**: `scp`로 전송 후 라즈베리파이에서 실행하여 `pointer size: 8 bytes` 출력 확인
3. **방법 B 및 방법 C 검증**: 각 방식으로 생성된 결과물의 `file` 속성을 방법 A 결과와 상호 대조
4. **성능 벤치마크**: 라즈베리파이 현장 네이티브 빌드 소요 시간과 호스트 PC 크로스 빌드 소요 시간 측정·비교

### 고찰 항목

- **빌드 성능 비교**: 네이티브 빌드와 크로스 빌드의 소요 시간 차이를 **정량적 측정값(초 단위)**으로 제시
- **빌드 방식별 특성 분석**: 방법 A(툴체인 직접 사용), 방법 B(CMake 툴체인 파일), 방법 C(도커)의 장단점을 비교하고 각 방식이 적합한 적용 환경 설명
