<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 1 - 크로스 컴파일

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 1 - 목표 (Goals)

- 호스트 PC에서 라즈베리파이용 **arm64 바이너리** 생성

### 준비물

| 항목        | 내용                                       |
| ----------- | ------------------------------------------ |
| 호스트      | x86_64 리눅스(또는 **도커**가 동작하는 PC) |
| 타깃        | 같은 네트워크에 있는 라즈베리파이          |
| 확인할 정보 | 타깃의 IP 주소와 로그인 계정               |

---

## 실습 1 - 구성 (Layout)

```text
mep/lab01/
├── CMakeLists.txt                        # build description
├── Dockerfile                            # pinned build environment
├── cmake/
│   └── toolchains/
│       └── aarch64-linux-gnu.cmake       # which compiler to use
└── src/
    └── helloworld.cc                 # no libraries at all
```

---

## 실습 1 - 예제 코드 (Example)

[//]: # "INCLUDE: ./mep/10/src/helloworld.cc"

- `sizeof(void*)`를 출력하는 이유: 타깃에서 **8**이 나와야 arm64 바이너리임
- `file`을 사용해 바이너리의 아키텍처가 타깃 아키텍처인지 확인 필요

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

- 툴체인은 `aarch64-linux-gnu-` **접두사**를 가진 컴파일러 모음
- `g++`를 사용하면 네이티브 빌드가 수행되어 **호스트용 바이너리**가 생성됨

---

## 실습 1 - 아키텍처 확인 (Verify the Target)

- 크로스 빌드에서 **가장 많이 하는 실수**: 네이티브 빌드를 수행한 후 이를 타깃 환경에서 사용하는 것

```bash
file hello_pi
# ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), ...
```

| 출력 결과            | 뜻                                                     |
| -------------------- | ------------------------------------------------------ |
| `ARM aarch64`        | 타깃용 — 맞게 생성됨                                   |
| `x86-64`             | 호스트용 — 크로스 컴파일이 아닌 네이티브 빌드가 수행됨 |
| `dynamically linked` | 타깃에 해당 `.so`가 있어야 실행됨                      |
| `statically linked`  | 단독 실행 가능                                         |

- 아키텍처가 다르면 타깃에서 `cannot execute binary file: Exec format error` 오류가 발생함

---

## 실습 1 - 방법 B: CMake 툴체인 파일 (Toolchain File) 사용

[//]: # "INCLUDE: ./mep/10/cmake/toolchains/aarch64-linux-gnu.cmake"

---

## 실습 1 - 방법 B: CMake 툴체인 파일 (Toolchain File) 사용 (Cont'd)

[//]: # "INCLUDE: ./mep/10/CMakeLists.txt"

```bash
cmake -B build-pi \
    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/aarch64-linux-gnu.cmake \
    -DCMAKE_BUILD_TYPE=Release
cmake --build build-pi -j
file build-pi/hello_pi
```

---

## 실습 1 - 방법 C: 도커 (Pinned Environment)

- 도커 이미지 안에 툴체인 등 빌드 환경을 관리하는 방식
- 일관된 빌드 환경을 간편하게 설정 가능

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

- 소스를 **읽기 전용**(`:ro`)으로 마운트하여 컨테이너가 작업 트리를 수정하지 못하게 설정
- 도커 이미지는 CI 파이프라인에서도 그대로 활용 가능
  - CI 환경 구축을 빠르게 완료하고 로컬과 동일한 테스트 환경을 보장할 수 있음

---

## 실습 1 - 전송과 실행 (Transfer and Run)

```bash
# 1. Find the target's address (run on the Pi, or check the router)
hostname -I                    # e.g. 192.168.0.42

# 2. Copy the binary from the host to the Pi
scp hello_pi <user>@192.168.0.42:~/
#      ^ source       ^ destination

# 3. Log in and run it on the target
ssh <user>@192.168.0.42
chmod +x hello_pi              # restore the executable bit if needed
./hello_pi
# Hello, World!
# pointer size: 8 bytes
```

- `scp <로컬 파일> <사용자>@<주소>:<원격 경로>`
- `ssh-copy-id <사용자>@<주소>`로 키를 등록하면 비밀번호 입력 과정을 생략할 수 있음

---

## 실습 1 - 한 줄로 잇기 (One-Liner)

- 빌드 → 전송 → 실행을 묶어 수정과 확인 과정을 간편하게 수행

```bash
aarch64-linux-gnu-g++ -std=c++14 src/helloworld.cc -o hello_pi \
  && scp hello_pi <user>@192.168.0.42:~/ \
  && ssh <user>@192.168.0.42 './hello_pi'
```

- `&&`로 각 명령들을 연결했을 때, **앞 단계 명령이 실패했을 때 뒤따르는 명령어는 실행되지 않고 즉시 종료됨**

---

## 실습 1 - 과제 (Tasks)

1. 방법 A로 빌드한 뒤 `file`로 `ARM aarch64`임을 확인
2. `scp`로 전송해 라즈베리파이에서 실행하고, 출력이 `8 bytes`인지 확인
3. 방법 B와 방법 C로도 빌드하여 세 결과물의 `file` 출력을 비교
4. 라즈베리파이에서 직접 빌드한 시간과 크로스 빌드 시간을 측정해 비교

### 고찰 항목

- 두 방식의 빌드 시간 차이를 **측정값으로** 제시
- 방법 A(툴체인 직접 사용), B(CMake 툴체인 파일), C(도커)의 장단점을 비교하고, 각 방식이 적합한 상황을 설명
