<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 1 - 크로스 컴파일

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 1 - 목표 (Goals)

- **목표**: 호스트 PC에서 라즈베리파이용 **64비트 ARM(arm64) 실행 파일**을 크로스 컴파일하고 타깃에서 실행
- **크로스 컴파일**: 프로그램을 실행할 컴퓨터(타깃)와 다른 아키텍처의 컴퓨터(호스트)에서 빌드하는 방식
  - 예: x86_64 PC에서 `aarch64-linux-gnu-g++`로 빌드한 파일을 라즈베리파이에서 실행
- **필요성**: 라즈베리파이에서 직접 빌드하면 CPU·메모리가 작아 큰 프로젝트의 빌드 시간이 길어짐

### 실습 환경 및 준비 사항

| 구분 | 요구 환경 및 상세 내용 |
| :--- | :--------------------- |
| **호스트 PC** | x86_64 리눅스(또는 Docker를 실행할 수 있는 환경) |
| **타깃 보드** | 같은 로컬 네트워크에 연결된 라즈베리파이(Raspberry Pi OS 64-bit) |
| **확인 정보** | 타깃 보드의 IP 주소와 SSH 로그인 계정·비밀번호 |

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

- **`CMakeLists.txt`**: 빌드할 실행 파일과 C++ 표준을 지정하는 CMake 빌드 설명 파일
- **`Dockerfile`**: 툴체인과 CMake를 설치한 빌드 환경을 정의하는 파일(방법 C)
- **`aarch64-linux-gnu.cmake`**: CMake가 사용할 크로스 컴파일러를 지정하는 툴체인 파일(방법 B)
- **`helloworld.cc`**: 라이브러리를 쓰지 않는 예제이므로, 실패하면 하드웨어가 아니라 빌드 설정의 문제임

---

## 실습 1 - 예제 코드 (Example)

[//]: # "INCLUDE: ./mep/10/src/helloworld.cc"

- **포인터 크기 확인**: arm64 빌드는 `sizeof(void*)`가 8이므로 `pointer size: 8 bytes`를 출력
  - 32비트 ARM(armhf)용으로 잘못 빌드하면 `4 bytes`를 출력
- **아키텍처 확인**: 빌드 직후 `file` 명령으로 실행 파일의 아키텍처를 반드시 확인

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

- **툴체인**: 컴파일러·어셈블러·링커와 타깃용 표준 라이브러리를 묶은 빌드 도구 모음
- **접두사**(prefix): `aarch64-linux-gnu-`는 타깃의 아키텍처(`aarch64`)·OS(`linux`)·C 라이브러리(`gnu`)를 나타냄
- **접두사가 없는 `g++`**: 호스트용(x86_64) 실행 파일을 만들므로 라즈베리파이에서 실행되지 않음

---

## 실습 1 - 아키텍처 확인 (Verify the Target)

- **흔한 실수**: 호스트용으로 빌드한 실행 파일을 라즈베리파이에 복사하여 실행하려는 경우

```bash
file hello_pi
# ELF 64-bit LSB pie executable, ARM aarch64, version 1 (SYSV), dynamically linked, ...
```

| 출력 문자열 | 의미 |
| :--- | :--- |
| `ARM aarch64` | **타깃용**: 라즈베리파이 64비트 환경에서 실행 가능 |
| `x86-64` | **호스트용**: 크로스 컴파일이 아닌 호스트 컴파일러로 빌드됨 |
| `pie executable` | **PIE**(Position-Independent Executable): 적재 주소가 고정되지 않은 실행 파일 |
| `dynamically linked` | **동적 링크**: 실행 시 타깃의 공유 라이브러리(`.so`)를 사용 |
| `statically linked` | **정적 링크**: 외부 `.so` 없이 실행 |

- **확인 조건**: Ubuntu 22.04의 `aarch64-linux-gnu-g++` 11.4로 빌드한 결과

---

## 실습 1 - 아키텍처 확인 (Verify the Target) (Cont'd - 1)

### 실행 오류와 원인

- **아키텍처 불일치**: x86_64 실행 파일을 라즈베리파이에서 실행하면 셸이 오류를 출력
  - `cannot execute binary file: Exec format error`
- **C 라이브러리 버전 불일치**: 호스트 툴체인의 glibc가 타깃보다 새로우면 실행 시 `GLIBC_2.xx not found` 오류
  - **glibc**: 리눅스의 표준 C 라이브러리(`libc.so.6`)이며, 동적 링크된 실행 파일은 타깃의 glibc를 사용
  - **확인 방법**: `aarch64-linux-gnu-objdump -T hello_pi | grep GLIBC`로 요구하는 최고 버전 확인
  - 예: 이 예제를 Ubuntu 24.04 컨테이너(방법 C)에서 빌드하면 최고 요구 버전은 `GLIBC_2.34`

---

## 실습 1 - 방법 B: CMake 툴체인 파일 사용 (Toolchain File)

[//]: # "INCLUDE: ./mep/10/cmake/toolchains/aarch64-linux-gnu.cmake"

- **`CMAKE_SYSTEM_NAME`·`CMAKE_SYSTEM_PROCESSOR`**: 타깃의 OS와 CPU를 지정하여 크로스 컴파일 모드로 전환
- **`CMAKE_CXX_COMPILER`**: 호스트 기본 컴파일러 대신 사용할 크로스 컴파일러
- **`CMAKE_FIND_ROOT_PATH_MODE_*`**: 실행 프로그램은 호스트에서, 헤더·라이브러리는 타깃용 경로에서만 검색

---

## 실습 1 - 방법 B: CMake 툴체인 파일 사용 (Toolchain File) (Cont'd - 1)

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

- **`-DCMAKE_TOOLCHAIN_FILE`**: 구성 단계에서 툴체인 파일을 읽어 크로스 컴파일러를 선택
- **방법 A와의 차이**: 컴파일러 지정이 파일 하나에 모이므로 소스 파일이 늘어도 명령은 그대로임

---

## 실습 1 - 방법 C: 도커 (Pinned Environment)

- **Docker**: 운영체제 위에서 격리된 실행 환경(컨테이너)을 만들어 프로그램을 실행하는 도구
- **이미지**: 컨테이너를 만드는 데 쓰는 읽기 전용 템플릿이며, `Dockerfile`로 정의
- **빌드 환경 고정**: 툴체인·CMake의 버전을 이미지에 고정하므로 호스트 설정과 관계없이 같은 결과물 생성

[//]: # "INCLUDE: ./mep/10/Dockerfile"

---

## 실습 1 - 방법 C: 도커 (Pinned Environment) (Cont'd - 1)

### `Dockerfile`의 구성

- **`FROM ubuntu:24.04`**: Ubuntu 24.04 이미지를 기반으로 시작
- **`RUN apt-get install ...`**: 크로스 컴파일러(`g++-aarch64-linux-gnu`)와 CMake를 이미지에 설치
  - `--no-install-recommends`: 필수가 아닌 추천 패키지를 설치하지 않아 이미지 크기를 줄임
  - `rm -rf /var/lib/apt/lists/*`: 설치 후 패키지 목록 캐시를 삭제하여 이미지 크기를 줄임
- **`WORKDIR /src`**: 이후 명령의 작업 디렉터리를 `/src`로 지정
- **`CMD`**: 컨테이너를 실행하면 `/src`의 소스를 구성하고 `/out`에 빌드
  - 여러 줄로 나눈 명령은 각 줄 끝에 `\`를 붙여야 하며, 빠지면 `docker build`가 `unknown instruction`으로 실패

---

## 실습 1 - 방법 C: 도커 빌드 (Building in a Container)

```bash
cd mep/lab01

docker build -t mep-lab01 .
mkdir -p out

# Mount the source read-only, write the build output to ./out
docker run --rm \
  --user "$(id -u):$(id -g)" \
  -v "$PWD":/src:ro \
  -v "$PWD/out":/out \
  mep-lab01

file out/hello_pi
```

- **`docker build -t mep-lab01 .`**: 현재 디렉터리의 `Dockerfile`로 `mep-lab01` 이미지를 생성
- **`-v "$PWD":/src:ro`**: 소스 디렉터리를 컨테이너의 `/src`에 **읽기 전용**으로 연결하여 소스 변경을 방지
- **`--user`**: 현재 사용자 권한으로 실행하며, 생략하면 `out/`의 파일이 root 소유가 되어 일반 계정으로 지울 수 없음
  - `mkdir -p out`: `out/`이 없으면 Docker가 root 소유로 만들어 `--user` 계정이 쓸 수 없으므로 미리 생성
- **`--rm`**: 실행이 끝난 컨테이너를 자동으로 삭제
- **CI 재사용**: 같은 이미지를 GitHub Actions 같은 CI 환경에서 그대로 사용할 수 있음(8장)

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

---

## 실습 1 - 전송과 실행 (Transfer and Run) (Cont'd - 1)

- **SSH**(Secure Shell): 네트워크로 다른 컴퓨터에 암호화된 연결을 맺어 명령을 실행하는 프로토콜
- **`scp`**: SSH 연결로 파일을 복사하는 명령
  - 형식: `scp <로컬 파일> <사용자>@<주소>:<원격 경로>`
- **`hostname -I`**: 라즈베리파이에서 실행하면 네트워크 인터페이스에 할당된 IP 주소를 출력
- **`chmod +x`**: 실행 권한이 없으면 `Permission denied`로 실행되지 않으므로 실행 권한을 부여
- **SSH 키 인증**: `ssh-copy-id <사용자>@<주소>`로 공개키를 등록하면 이후 비밀번호를 묻지 않음
  - 아래의 한 줄 명령처럼 `scp`·`ssh`를 반복 실행할 때 비밀번호 입력을 없앰

---

## 실습 1 - 한 줄로 잇기 (One-Liner)

- **목적**: 빌드 → 전송 → 타깃 실행을 명령 하나로 묶어 수정할 때마다 반복하는 시간을 줄임

```bash
# Build, transfer, and execute on the target in a single pipeline
aarch64-linux-gnu-g++ -std=c++14 src/helloworld.cc -o hello_pi \
  && scp hello_pi <user>@192.168.0.42:~/ \
  && ssh <user>@192.168.0.42 './hello_pi'
```

- **`&&`**: 앞 명령이 성공(종료 코드 0)한 경우에만 다음 명령을 실행
  - 예: 컴파일 오류가 나면 `scp`와 `ssh`를 실행하지 않으므로 이전 실행 파일이 타깃에서 실행되지 않음
- **`ssh <주소> '<명령>'`**: 로그인 셸을 열지 않고 원격에서 명령 하나만 실행한 뒤 출력을 호스트에 표시

---

## 실습 1 - 과제 (Tasks)

1. **방법 A**: 툴체인으로 빌드한 뒤 `file` 명령으로 `ARM aarch64`인지 확인
2. **타깃 실행**: `scp`로 전송한 뒤 라즈베리파이에서 실행하여 `pointer size: 8 bytes` 출력 확인
3. **방법 B·C**: 각 방법으로 만든 실행 파일의 `file` 출력을 방법 A의 결과와 비교
4. **빌드 시간 측정**: 같은 소스를 라즈베리파이에서 직접 빌드한 시간과 호스트에서 크로스 빌드한 시간을 비교
   - `time` 명령을 앞에 붙여 실행하면 소요 시간(`real`)을 출력

### 고찰 항목

- **빌드 시간 비교**: 직접 빌드와 크로스 빌드의 소요 시간 차이를 **초 단위 측정값**으로 제시
- **빌드 방법 비교**: 방법 A(툴체인 직접 사용), B(CMake 툴체인 파일), C(도커)의 장단점과 적합한 상황을 설명
