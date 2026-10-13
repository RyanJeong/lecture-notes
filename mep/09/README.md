<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 준비와 GPIO 기초

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 공통 규칙 (Common Rules)

- **3인 1조**로 수행
- 배선 변경 시 **반드시 전원을 차단**할 것
- LED는 항상 전류 제한 저항과 직렬로 연결
- GPIO는 **3.3V 로직** — 5V 신호를 직접 연결하지 말 것
  - 거리 센서 실습의 5V Echo 신호도 분압 후 연결

### 보고서 제출

- 실습 목표, 회로 구성, 소스 코드, 실행 결과, 고찰 순으로 작성
- 실행 결과는 **직접 촬영한 영상**을 포함
  - 영상에는 적어도 한 명 이상의 조원이 등장해야 함
- 코드는 전체를 붙여넣지 말고 핵심 부분만 발췌해 설명

### (Opt.) 사전 학습 자료 (Preparation Material)

- [Basic Unix commands](https://www.youtube.com/watch?v=3DA1grSp4mU)
- [Basic Linux Navigation](https://www.youtube.com/watch?v=dzHscTzpAME)
- [The vi Text Editor - Basic Intro](https://www.youtube.com/watch?v=KtTjamPKMhw)

---

## 실습 구성 (Lab Overview)

| 실습 | 주제                     |
| ---- | ------------------------ |
| 1    | 크로스 컴파일            |
| 2    | LED·스위치·PWM·상태 기계 |
| 3    | 온습도·조도·거리 센서    |
| 4    | 센서 통합 웹 서버        |
| 5    | 오디오 시각화·녹음       |
| 6    | 사진·영상 촬영           |
| 7    | 웹캠 기반 CCTV           |

- 실습 2~4는 GPIO 접근 및 제어에 공유 헤더(`gpio.hpp`) 사용
- 실습 5~7은 오디오·영상 처리에 ALSA(Advanced Linux Sound Architecture)·V4L2(Video4Linux2) 표준 API 사용

---

## 공통 개발 흐름 (Workflow)

- 모든 실습이 공유하는 헤더는 `mep/common/` 한 곳에만 보관

```text
mep/
├── common/
│   ├── gpio.hpp           # one GPIO line, RAII
│   └── signal_stop.hpp    # Ctrl-C stop flag
├── lab02/src/             # LED, PWM, state machine
├── lab03/src/             # sensors
├── lab04/src/             # web service
...
```

```bash
cd mep/lab02/src

# Build -- -I points at the shared headers
clang++ -std=c++14 -Wall -Wextra -I../../common 00_led_button.cc -o led -lgpiod

./led                    # run
gpioinfo -c gpiochip0    # libgpiod v2: inspect the selected chip
```

---

## 패키지 설치 (Packages)

| 패키지           | 용도                              |
| ---------------- | --------------------------------- |
| `clang`          | 모든 실습의 컴파일러              |
| `libgpiod-dev`   | GPIO 제어(실습 2~4)               |
| `gpiod`          | `gpioinfo`·`gpiodetect` 점검 도구 |
| `liblgpio-dev`   | 마이크로초 타이밍(거리 센서)      |
| `libasound2-dev` | 오디오 캡처(실습 5)               |
| `alsa-utils`     | `arecord`·`aplay` 점검 도구       |
| `v4l-utils`      | `v4l2-ctl` 카메라 점검 도구       |
| `pkg-config`     | libgpiod 개발 패키지 버전 확인    |

```bash
sudo apt update
sudo apt install -y \
    clang libgpiod-dev gpiod \
    liblgpio-dev libasound2-dev alsa-utils \
    v4l-utils pkg-config
```

---

## GPIO 기초 - 디지털 입출력 (Digital I/O Basics)

![h:150 center](img/00-logic-levels.png)

| 상태    | 라즈베리파이(3.3V 로직)                      |
| ------- | -------------------------------------------- |
| LOW(0)  | 0V에 가까운 유효 입력 전압                   |
| HIGH(1) | 3.3V에 가까운 유효 입력 전압                 |
| 불확정  | LOW·HIGH 보장 범위 사이 — 논리값 보장 불가   |

- LOW·HIGH 판정 임계값은 보드·GPIO 컨트롤러 데이터시트에서 확인

---

## GPIO 기초 - 풀업·풀다운 (Pull-Up and Pull-Down)

![h:220 center](img/23-pull-up-down.svg)

| 방식 | 저항 연결 | 버튼 연결 | 놓음(개방) | 누름(닫힘) |
| ---- | --------- | --------- | ---------- | ---------- |
| 풀업 | 입력 ↔ 3.3V | 입력 ↔ GND | HIGH | LOW |
| 풀다운 | 입력 ↔ GND | 입력 ↔ 3.3V | LOW | HIGH |

- 버튼이 열려 입력의 기본 전압을 정해 주는 연결이 없으면 입력값이 정해지지 않는 **플로팅** 상태가 됨
- 플로팅 입력은 주변 잡음이나 누설 전류의 영향을 받아 버튼을 누르지 않았음에도 값이 바뀐 것처럼 읽힐 수 있음
- 풀업·풀다운 저항은 버튼을 놓았을 때도 입력을 각각 3.3V 또는 GND에 연결해 안정된 기본값을 사용
  - 풀업은 **액티브 LOW**(LOW가 눌림), 풀다운은 **액티브 HIGH**(HIGH가 눌림)

---

## GPIO 기초 - Gpio API (Wrapper API)

| API | 동작·반환값 |
| --- | ----------- |
| `Gpio(line, mode, chip)` | 칩의 라인 오프셋을 요청; 기본 칩 경로는 `/dev/gpiochip0` |
| `ok()` | 라인 요청 성공 여부 |
| `Get()` | 입력값 `0`(LOW)·`1`(HIGH); 실패는 `-1` |
| `Set(value)` | 출력값 설정; `0`은 LOW, 그 외 값은 HIGH; 성공 여부 `bool` |
| `Reconfigure(mode)` | 기존 요청을 해제하고 새 방향·설정으로 다시 요청 |
| `Release()` | 현재 라인 요청 해제; 요청이 없어도 호출 가능 |

- `gpio.hpp`가 라인 확보와 해제를 전담하여 중복 코드 제거
- `line`은 헤더의 **물리 핀 번호가 아닌 gpiochip의 라인 오프셋**
- BCM 번호와 라인 오프셋의 대응은 보드·커널에서 확인
- 모드: `kOutputLow`, `kOutputHigh`, `kInput`, `kInputPullUp`

---

## GPIO 기초 - Gpio 수명·재설정 (Lifetime and Reconfiguration)

[//]: # "INCLUDE: ./mep/11/src/00_led_button.cc --from 27 --to 32 --no-comment"

- 생성자는 기본 칩을 열고 요청을 시도; **`ok()`로 성공 여부 확인**
- `Reconfigure()`는 현재 요청을 먼저 해제한 뒤 새 요청을 수행
  - 재설정 실패 시 이전 요청은 복구되지 않으며, 새 요청도 없는 상태
- 소멸자는 요청을 해제하고 칩을 닫음; 복사 생성·대입은 금지
- GPIO를 사용하기 전 요청 성공을 확인하고, 모든 `Get()`·`Set()` 반환값을 처리

---

## GPIO 기초 - 해제 순서 (Releasing in Reverse)

### 확보되는 자원과 사용 기간

- `Gpio`는 커널에 **특정 gpiochip의 한 라인 사용을 요청**하고, 성공하면 `gpiod_line_request`를 보유
- 생성 또는 `Reconfigure()`가 성공한 시점부터 `Release()`·재설정·소멸자까지 해당 라인을 점유
- 이 기간에 **다른 프로세스가 같은 라인을 요청하면** `Device or resource busy`로 실패할 수 있음

### 해제 순서와 종료

- 생성 순서: 칩 핸들 열기 → 라인 요청; 해제 순서: 라인 요청 반환 → 칩 핸들 닫기
- 조기 `return`·예외로 `Gpio` 소멸자가 실행되면 자원을 **획득 역순으로 해제**
- 프로세스가 끝나면 커널이 라인 요청을 회수하지만, 강제 종료에서는 소멸자가 실행되지 않음
- 라인 해제 뒤 GPIO 출력이 LOW가 된다는 보장은 없음; 안전한 출력 상태는 회로·하드웨어에서 별도 설계

---

## GPIO 기초 - 헤더 핀 배치 (Header Pinout)

![h:500 center](img/22-rpi-pinout.png)

---

## GPIO 기초 - 출력 회로와 전류 (Output and Current)

![h:100 center](img/01-gpio-led.png)

- GPIO 출력은 **전류를 공급하거나 흡수**하며 소자를 구동

### LED 회로

![h:200 center](img/02-led.png)

- LED는 **극성이 있음** — 새 부품의 긴 다리는 보통 애노드(+); 데이터시트로 확인
- 저항이 없으면 과전류로 **LED와 GPIO 핀이 모두 손상**됨

---

## GPIO 기초 - 출력 회로와 전류 (Output and Current) (Cont'd)

### 저항

![h:250 center](img/03-register.png)

### 전류 한계

- 핀당·전체 전류 한도와 권장 동작 조건은 보드 데이터시트에서 확인
- 절대 최대 정격은 설계 목표가 아님; 모터·릴레이는 **트랜지스터나 드라이버** 사용

---

## 실습 환경 확인 (Environment Check)

```bash
# Architecture and OS
uname -m                 # must report aarch64
cat /etc/os-release
clang++ --version

# GPIO
gpiodetect               # identify the chip exposing the header GPIO lines
pkg-config --modversion libgpiod
ldconfig -p | grep lgpio

# Camera and microphone
v4l2-ctl --list-devices
arecord -l

# Grant access (takes effect after re-login)
# Check the groups available on this Raspberry Pi OS installation.
getent group gpio video audio
# Example only when all three groups exist:
sudo usermod -aG gpio,video,audio "$USER"
```

---

## 부록 - 공용 코드 (Appendix: Shared Code)

- 실습 2부터 4까지가 공유하는 헤더는 두 개뿐

| 파일              | 역할                  |
| ----------------- | --------------------- |
| `gpio.hpp`        | GPIO 라인 확보와 해제 |
| `signal_stop.hpp` | Ctrl-C 정지 플래그    |

- 센서 프로토콜은 래퍼에 숨기지 않고 **각 실습 코드에서 직접 구현**
- 오디오·영상 실습도 종료 처리를 위해 `signal_stop.hpp` 사용 가능

---

## 부록 - gpio.hpp

[//]: # "INCLUDE: ./mep/common/gpio.hpp --to 19"

- 네 모드로 출력의 초기값을 정하거나, 입력에 내부 풀업을 적용할지 선택

---

## 부록 - gpio.hpp (Cont'd - 1)

[//]: # "INCLUDE: ./mep/common/gpio.hpp --from 20 --to 33"

- 생성자는 칩을 열고 첫 라인 요청을 설정; 소멸자는 라인을 해제한 뒤 칩을 닫음
- GPIO 자원을 복사하지 못하게 막고, `ok()`로 라인 요청 성공 여부를 확인

---

## 부록 - gpio.hpp (Cont'd - 2)

[//]: # "INCLUDE: ./mep/common/gpio.hpp --from 34 --to 51"

- `Get()`은 LOW `0`, HIGH `1`, 읽기 실패 `-1`을 반환
- `Set()`은 출력 설정 성공 여부를 `bool`로 반환

---

## 부록 - gpio.hpp (Cont'd - 3)

[//]: # "INCLUDE: ./mep/common/gpio.hpp --from 52 --to 68"

- `Reconfigure()`는 기존 요청을 해제한 뒤 새 방향과 모드로 라인을 다시 요청
- 단선 센서처럼 한 핀을 출력과 입력으로 번갈아 써야 할 때 사용

---

## 부록 - gpio.hpp (Cont'd - 4)

[//]: # "INCLUDE: ./mep/common/gpio.hpp --from 69 --to 85"

- 요청 성공 여부를 반환하고, 임시 설정 객체 세 개는 성공 여부와 무관하게 모두 해제
- `Release()`는 라인 요청을 해제하고 핸들을 비워; 소멸자에서도 호출

---

## 부록 - gpio.hpp (Cont'd - 5)

[//]: # "INCLUDE: ./mep/common/gpio.hpp --from 86 --to 99"

- 먼저 입력·출력 방향을 설정하고, `kInputPullUp`이면 내부 풀업을 요청
- 방향 또는 풀업 설정에 실패하면 `false`를 반환

---

## 부록 - gpio.hpp (Cont'd - 6)

[//]: # "INCLUDE: ./mep/common/gpio.hpp --from 100 --to 113"

- 일반 입력 `kInput`은 바이어스를 별도로 지정하지 않으므로, 회로에 풀 저항이 없으면 입력이 플로팅될 수 있음
- 출력 모드는 `kOutputLow` 또는 `kOutputHigh`에 따라 초기 출력값을 설정

---

## 부록 - signal_stop.hpp

[//]: # "INCLUDE: ./mep/common/signal_stop.hpp --to 20"

- 신호 처리기는 **`volatile sig_atomic_t` 플래그 하나만** 갱신
- `printf`·`malloc`·libgpiod 호출은 비동기 신호 안전이 아니므로 금지

---

## 부록 - signal_stop.hpp (Cont'd - 1)

[//]: # "INCLUDE: ./mep/common/signal_stop.hpp --from 21 --to 28"

- 루프가 종료 플래그를 확인한 뒤 반환하면 RAII 객체의 소멸자가 자원 해제

---

## 부록 - signal_stop.hpp (Cont'd - 2)

[//]: # "INCLUDE: ./mep/common/signal_stop.hpp --from 29"

- `SIGHUP`도 처리하여 SSH 종료 시 루프를 통한 종료·정리 시도
- 연결 종료가 항상 `SIGHUP`을 발생시키지는 않음; `SIGKILL`은 처리 불가
