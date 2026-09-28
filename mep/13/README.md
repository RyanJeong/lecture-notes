<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 크로스 컴파일 실습

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 이 장의 구성 (Contents)

| 구분 | 내용                                        |
| ---- | ------------------------------------------- |
| 준비 | 툴체인 설치와 확인                          |
| 실행 | 단일 파일 → CMake → 도커 순으로 크로스 빌드 |
| 검증 | 아키텍처 확인과 타깃 실행                   |

- 3장에서 배운 개념을 **실제로 수행**해 보는 장

---

## 왜 크로스 컴파일을 실습하는가 (Why It Matters)

- 지금까지는 라즈베리파이에서 직접 빌드했음. 그 방식의 한계를 체감하는 것이 목적

| 항목        | 타깃에서 직접 빌드      | 호스트에서 크로스 빌드         |
| ----------- | ----------------------- | ------------------------------ |
| 빌드 속도   | 보드 자원에 제한        | 호스트 자원 활용 가능          |
| CI 자동화   | 장치 러너가 있으면 가능 | 호스티드 러너에서도 가능       |
| 환경 재현성 | 장치마다 다를 수 있음   | 도커로 고정                    |
| 초기 설정   | 타깃 개발 패키지 필요   | 툴체인과 타깃 의존성 준비 필요 |

> 프로젝트가 커질수록 **초기 설정 비용보다 빌드 시간 절약이 커짐**

---

## 실습 09 - 크로스 컴파일 실습

- 호스트 PC에서 arm64 바이너리를 생성
- 툴체인과 sysroot의 역할을 실제로 확인
- 빌드 시간을 비교해 크로스 컴파일의 이점을 체감

### 준비

```bash
# Install the cross toolchain on the host (x86_64 Linux)
sudo apt install -y g++-aarch64-linux-gnu

aarch64-linux-gnu-g++ --version
```

---

## 실습 09 - 구성과 빌드 (Layout and Build)

```text
project/13/src/
└── 00_hello_cross.cc          # minimal example with no library dependency
```

```bash
# On the HOST, not on the Raspberry Pi
cd project/13/src
aarch64-linux-gnu-g++ -std=c++14 -Wall -Wextra \
        00_hello_cross.cc -o hello_pi
```

- 이 예제는 `-lgpiod`도, `-I../../common`도 필요 없음 — **`common/` 의존성이 없는** 유일한 실습
  - 실습 01~05를 크로스 빌드할 때는 `-I../../common`이 필요하며, 그 코드는 9장 부록에 있음
  - 툴체인만 검증하는 것이 목적이므로 **의존성을 0으로** 둔 것
- 여기서 실패하면 원인은 툴체인 하나뿐 — 하드웨어를 의심할 필요가 없음

---

## 실습 09 - 예제 코드 (Example)

[//]: # "INCLUDE: ./mep/13/src/00_hello_cross.cc --from 7 --to 13 --no-comment"

- `sizeof(void*)`를 출력하는 이유: 타깃에서 **8**이 나와야 arm64 바이너리임
- 호스트에서 실수로 네이티브 빌드했다면 이 프로그램은 호스트에서도 잘 돌아감
  - 그래서 다음 슬라이드의 `file` 확인이 반드시 필요

---

## 실습 09 - 아키텍처 확인 (Verify the Target)

- 크로스 빌드에서 **가장 많이 하는 실수**는 호스트용 바이너리를 만들고 모르는 것

```bash
file hello_pi
# ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), ...
```

| 출력에 보이는 것     | 뜻                                            |
| -------------------- | --------------------------------------------- |
| `ARM aarch64`        | 타깃용 — 맞게 만들어짐                        |
| `x86-64`             | 호스트용 — 툴체인이 아니라 기본 `g++`를 쓴 것 |
| `dynamically linked` | 타깃에 해당 `.so`가 있어야 실행됨             |
| `statically linked`  | 단독 실행 가능                                |

- 실행해 보기 전에 `file`로 확인하는 습관을 들일 것
  - 아키텍처가 다르면 타깃에서 `cannot execute binary file: Exec format error`

---

## 실습 09 - 전송과 실행 (Transfer and Run)

```bash
# 1. Find the target's address (run on the Pi, or check the router)
hostname -I                    # e.g. 192.168.0.42

# 2. Copy the binary from the host to the Pi
scp hello_pi <user>@192.168.0.42:~/
#      ^ source          ^ destination  ^ remote home directory

# 3. Log in
ssh <user>@192.168.0.42

# 4. Run it on the target
chmod +x hello_pi              # verify or restore the executable bit
./hello_pi
# Hello, World!
# pointer size: 8 bytes
```

- `scp <로컬 파일> <사용자>@<주소>:<원격 경로>` — 방향은 항상 **왼쪽에서 오른쪽**
  - 반대로 가져올 때는 `scp <사용자>@<주소>:<원격 파일> .`
- 매번 비밀번호를 넣기 번거로우면 `ssh-copy-id <사용자>@<주소>`로 키를 등록

---

## 실습 09 - 한 줄로 잇기 (One-Liner)

- 빌드 → 전송 → 실행을 한 번에 묶으면 수정-확인 주기가 짧아짐

```bash
aarch64-linux-gnu-g++ -std=c++14 00_hello_cross.cc -o hello_pi \
  && scp hello_pi <user>@192.168.0.42:~/ \
  && ssh <user>@192.168.0.42 './hello_pi'
```

- `&&`로 이어 두면 **앞 단계가 실패하면 뒤가 실행되지 않음**
  - 빌드가 깨졌는데 이전 바이너리가 실행되어 혼란스러워지는 상황을 막아 줌

### CMake 툴체인 파일 사용

```bash
cmake -B build-pi \
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/aarch64-linux-gnu.cmake \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build-pi -j
```

---

## 실습 09 - 과제 (Tasks)

1. `00_hello_cross.cc`를 크로스 빌드하고 `file`로 `ARM aarch64`임을 확인
2. `scp`로 전송해 라즈베리파이에서 실행하고, 출력이 `8 bytes`인지 확인
3. 일부러 `clang++`로 빌드해 타깃에서 `Exec format error`를 재현해 볼 것
4. 실습 01~05 중 하나를 골라 크로스 컴파일로 빌드 — `-lgpiod`에서 막히는 지점을 기록
5. 라즈베리파이에서 직접 빌드한 시간과 크로스 빌드 시간을 측정해 비교

### 고찰 항목

- 두 방식의 빌드 시간 차이를 **측정값으로** 제시
- 라이브러리(`-lgpiod`)를 링크할 때 어떤 문제가 발생했는가
  - sysroot가 필요한 이유를 실제 오류 메시지와 함께 설명
- `file`로 아키텍처를 확인하지 않으면 어떤 문제가 생기는가

---

## 라이브러리 링크 문제 (Linking Against Target Libraries)

- 단일 파일은 쉽게 크로스 컴파일되지만, **라이브러리를 링크하는 순간** 문제가 생김

```bash
aarch64-linux-gnu-g++ blink.cc -o blink -lgpiod
# /usr/bin/ld: cannot find -lgpiod
```

### 원인

- 호스트에 설치된 `libgpiod`는 **x86_64용** — arm64 링커가 쓸 수 없음
- 타깃용 헤더와 라이브러리가 담긴 **sysroot**가 필요

### 해결 방법

| 방법                 | 설명                                                    |
| -------------------- | ------------------------------------------------------- |
| sysroot 구성         | 타깃의 `/usr`를 복사해 `--sysroot`로 지정               |
| 멀티아치 패키지      | `dpkg --add-architecture arm64` 후 `:arm64` 패키지 설치 |
| **도커 크로스 빌드** | 호스트 아키텍처 컨테이너에서 AArch64 툴체인 사용        |

> 실습에서는 도커 방식을 권장 — 3장의 `docker buildx`를 그대로 사용

---

## 13장 정리 (Summary)

- 크로스 컴파일은 **호스트에서 타깃용 바이너리**를 만드는 것
  - 툴체인은 `aarch64-linux-gnu-` 접두사를 가진 컴파일러 모음
- 결과물은 반드시 **`file`로 아키텍처를 확인** — 링크는 성공해도 타깃에서 실행 실패할 수 있음
- 라이브러리를 링크하려면 **sysroot**, 타깃 멀티아치 패키지, 또는 이를 갖춘 컨테이너가 필요
- 도커로 빌드 환경을 담으면 **"내 컴퓨터에서는 되는데"** 문제가 사라지고 CI에서도 동일하게 동작
- 빌드 시간을 실제로 측정해 두 방식의 차이를 확인할 것

> 다음 장에서 이 방식으로 최종 프로젝트를 빌드하고 배포함
