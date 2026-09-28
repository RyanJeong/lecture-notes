<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 멀티미디어 입출력

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 이 장의 구성 (Contents)

| 구분    | 내용                                    |
| ------- | --------------------------------------- |
| 실습 07 | 웹캠 마이크 — 오디오 표본화, RMS, 녹음  |
| 실습 08 | 웹캠 카메라 — V4L2, 영상 형식, 데이터량 |

- 센서와 달리 멀티미디어는 **데이터량이 폭발적으로 커짐** — 그것이 이 장의 주제

---

## 멀티미디어가 다른 점 (What Makes It Different)

| 항목                | 센서(3~11장) | 멀티미디어                  |
| ------------------- | ------------ | --------------------------- |
| 한 번에 얻는 데이터 | 수 바이트    | 수백 KB ~ MB                |
| 주기                | 초 단위      | 초당 수십 회                |
| CPU 부하            | 무시할 수준  | 상당함                      |
| 대역폭              | 문제 없음    | **병목이 됨**               |
| 압축                | 불필요       | 해상도·프레임률에 따라 필요 |

### 그래서 달라지는 것

- 버퍼 관리와 복사 횟수가 성능을 좌우
- 5장의 **SIMD**가 실제로 필요해지는 지점
- 1장에서 본 **영상 전용 SoC**(Ambarella 등)가 존재하는 이유

---

## 실습 준비 (Prerequisites)

- 사용 장비: **Logitech C270 USB 웹캠** — 카메라와 마이크가 한 몸에 들어 있음

```bash
# Audio: ALSA development headers, plus the CLI tools for checking
sudo apt install -y libasound2-dev alsa-utils

# Video: V4L2 CLI tools (the headers come with the kernel package)
sudo apt install -y v4l-utils

# Permissions -- take effect after logging out and back in
sudo usermod -aG audio,video "$USER"
```

### 실습 준비 장치 확인

```bash
arecord -l                     # capture devices: note the card,device numbers
v4l2-ctl --list-devices        # video devices: expect /dev/video0
v4l2-ctl -d /dev/video0 --list-formats-ext
```

- `arecord -l`이 출력한 번호가 예제의 `plughw:1,0`과 다르면 **실행 시 인자로 지정**할 것
- C270은 `/dev/video0`과 `/dev/video1` 두 개를 만들기도 함 — 캡처 가능한 쪽은 보통 `video0`

---

## 캡처 장치 지정 (Selecting the Capture Device)

- ALSA 장치 문자열은 `plughw:<카드 번호>,<장치 번호>` 형식

```text
$ arecord -l
**** List of CAPTURE Hardware Devices ****
card 3: U0x46d0x825 [USB Device 0x46d:0x825], device 0: USB Audio [USB Audio]
```

- 위 출력은 카드 `3`, 장치 `0` → 전달할 인자는 **`plughw:3,0`**

```bash
./00_audio_visualizer plughw:3,0
./01_wav_record plughw:3,0
```

- 인자를 생략하면 기본값 `plughw:1,0`을 사용하므로, 번호가 다르면 반드시 전달할 것
- USB 열거 순서에 따라 카드 번호가 바뀌므로, 실행 전 `arecord -l`로 재확인 권장

---

## ALSA란 (Advanced Linux Sound Architecture)

- 리눅스의 표준 오디오 계층. 커널 드라이버와 유저 공간 라이브러리(`libasound`)로 구성

| 개념             | 뜻                                                       |
| ---------------- | -------------------------------------------------------- |
| PCM              | 오디오 스트림 하나. 재생용과 캡처용이 따로 있음          |
| 카드 / 디바이스  | `hw:1,0` = 1번 카드의 0번 디바이스                       |
| `hw` vs `plughw` | `hw`는 형식을 그대로 요구, `plughw`는 필요하면 변환해 줌 |
| 프레임           | 모든 채널의 표본 하나 묶음. 모노는 1표본 = 1프레임       |
| 피리어드         | 드라이버가 한 번에 넘겨주는 프레임 수                    |

- 하드웨어 파라미터는 **명령이 아니라 협상** — `set_rate_near`는 가까운 값을 고르고, 실제로 채택된 값을 되돌려 줌. 그래서 예제는 요청값이 아니라 **반환값**을 사용

---

## ALSA - 오버런과 복구 (Overruns)

- 캡처 장치는 프로그램을 기다려 주지 않음. 읽어 가지 않으면 버퍼가 넘침
- 이때 `snd_pcm_readi`가 `-EPIPE`를 돌려줌 → **오버런**(overrun)

```text
driver   [####################] full -> new samples are dropped
program           ^ has only read up to here
```

- 오버런은 **오류가 아니라 늦었다는 신호** — `snd_pcm_recover`로 복구하고 계속하면 됨
  - 치명적 오류로 처리하면 CPU가 잠깐 바쁠 때마다 프로그램이 죽음
- 피리어드를 키우면 여유가 생기지만 **지연 시간**이 늘어남 — 둘은 맞바꾸는 관계

---

## 실습 07 - 웹캠 마이크 활용

- USB 웹캠의 **마이크**로 오디오를 입력받음
- CLI 오디오 비주얼라이저 구현
- `.wav` 형식으로 녹음

### 오디오 장치 확인

```bash
arecord -l                       # list capture devices
arecord -D plughw:1,0 -f cd -d 5 test.wav   # record 5 seconds
aplay test.wav                   # play it back
```

---

## 실습 07 - 오디오 기초 (Audio Basics)

<!-- IMAGE [다이어그램] 표본화와 양자화 개념도, RMS 계산 구간 표시 (img/18-audio-sampling.png) -->

| 항목      | 설명                            |
| --------- | ------------------------------- |
| 표본화율  | 초당 표본 수(예: 44100Hz)       |
| 비트 심도 | 표본 하나의 비트 수(예: 16비트) |
| 채널      | 모노(1) 또는 스테레오(2)        |

$$\text{Bytes per second} = \text{Sample rate} \times \frac{\text{Bit depth}}{8} \times \text{Channels}$$

- 44100Hz, 16비트, 스테레오 → 약 172KB/s

### 비주얼라이저 원리

- 일정 구간(프레임)의 표본에서 **진폭**을 계산
- 진폭에 비례한 길이의 막대를 터미널에 출력

$$RMS = \sqrt{\frac{1}{N}\sum_{i=1}^{N} x_i^2}$$

---

## 실습 07 - 구성과 빌드 (Layout and Build)

- 예제 두 개가 같은 캡처 래퍼를 공유
- 공용 헤더(`common/`)의 **전체 코드는 9장 부록**을 참조 — 필요한 부분은 이 장에서 발췌해 인용

```text
project/
├── common/
│   ├── alsa_capture.hpp       # RAII wrapper over PCM capture
│   └── signal_stop.hpp
└── 12/src/
    ├── 00_audio_visualizer.cc
    └── 01_wav_record.cc
```

- `-lasound`를 빠뜨리면 `undefined reference to snd_pcm_open`으로 링크가 실패

---

## 실습 07 - 빌드 명령 (Build Commands)

```bash
cd project/12/src

# 1) CLI visualizer
clang++ -std=c++14 -Wall -Wextra -I../../common \
        00_audio_visualizer.cc -o visualizer -lasound
./visualizer                   # Ctrl-C stops it at once
./visualizer plughw:3,0        # when `arecord -l` shows another card

# 2) WAV recorder
clang++ -std=c++14 -Wall -Wextra -I../../common \
        01_wav_record.cc -o wavrec -lasound
./wavrec                       # Ctrl-C finalises the file
aplay record.wav
```

---

## 실습 07 - 진폭 계산 (Amplitude)

- 평균이 아니라 **제곱평균제곱근** — 0을 중심으로 흔들리는 파형은 평균이 0에 가까움

[//]: # "INCLUDE: ./mep/12/src/00_audio_visualizer.cc --from 20 --to 38"

---

## 실습 07 - 막대 길이 (Bar Length)

- 사람의 청각은 로그 스케일이므로 dBFS 로 펴서 막대에 대응시킴

[//]: # "INCLUDE: ./mep/12/src/00_audio_visualizer.cc --from 40 --to 47"

- 무음일 때 $-\infty$로 발산하지 않도록 `kFloorDb`에서 잘라 냄

---

## 실습 07 - 비주얼라이저 루프 (Visualizer Loop)

- 신호를 받으면 **즉시 종료** — 기록한 것이 없으므로 마무리할 일도 없음

[//]: # "INCLUDE: ./mep/12/src/00_audio_visualizer.cc --from 67 --to 85"

---

## 실습 07 - 즉시 종료 (Immediate Exit)

[//]: # "INCLUDE: ./mep/12/src/00_audio_visualizer.cc --from 87 --to 91"

- 기록한 것이 없으므로 마감할 것도 없음 — 다시 그리던 줄만 닫아 주면 끝

---

## 실습 07 - WAV 헤더 (WAV Header)

- WAV은 RIFF 컨테이너 — 44바이트 헤더 뒤에 표본이 그대로 붙음
- 모든 다중 바이트 필드가 **리틀 엔디언**이므로 바이트 단위로 씀

[//]: # "INCLUDE: ./mep/12/src/01_wav_record.cc --from 41 --to 58"

---

## 실습 07 - 크기 필드 되메우기 (Patching the Sizes)

- Ctrl-C 는 이 프로그램의 **정상 종료 경로**이므로 반드시 마감 처리를 해야 함

[//]: # "INCLUDE: ./mep/12/src/01_wav_record.cc --from 116 --to 125"

- 마감하지 않고 죽으면 크기 필드가 0인 채로 남아 **재생기가 파일을 거부**함

---

## 실습 07 - 과제 (Tasks)

<!-- IMAGE [캡처] CLI 오디오 비주얼라이저 실행 터미널 캡처 (img/19-visualizer.png) -->

1. 비주얼라이저를 실행해 조용할 때와 말할 때의 dBFS 차이를 기록
2. Ctrl-C로 녹음을 마치고 `aplay record.wav`로 재생되는지 확인
3. 마감 처리를 일부러 건너뛴 뒤(`kill -9`) 파일이 재생되지 않음을 확인
4. 표본화율을 8000Hz로 낮춰 녹음하고, 음질 차이와 파일 크기를 비교
5. 일정 음량을 초과하면 LED를 켜는 소리 감지 기능을 추가

### 실습 07 고찰 항목

- 표본화율을 낮추면 어떤 소리가 사라지는가 — **나이퀴스트 정리**를 조사
- 조용한 환경과 시끄러운 환경의 RMS 값을 비교해 임계값을 정한 근거를 설명

---

## 실습 08 - 웹캠 카메라 활용

- USB 웹캠으로 사진과 영상을 촬영
- V4L2(Video4Linux2) 인터페이스의 개념을 이해
- 영상 데이터의 형식과 크기를 파악

### 영상 장치 확인

```bash
v4l2-ctl --list-devices
v4l2-ctl -d /dev/video0 --list-formats-ext   # supported formats and sizes
fswebcam -d /dev/video0 -r 640x480 shot.jpg  # capture a still
```

---

## 실습 08 - 영상 데이터 (Video Data)

<!-- IMAGE [그래프] 해상도별 초당 데이터량 비교 그래프, YUYV/MJPEG/H.264 비교표 (img/20-video-bandwidth.png) -->

| 형식  | 특징                        |
| ----- | --------------------------- |
| YUYV  | 무압축, 대역폭 큼           |
| MJPEG | 프레임 단위 JPEG 압축       |
| H.264 | 프레임 간 압축, 대역폭 작음 |

### 데이터량 계산

- 640×480, RGB24, 30fps 인 경우

$$640 \times 480 \times 3 \times 30 \approx 27.6\,MB/s$$

- USB 2.0의 실효 대역폭과 같은 버스의 다른 장치를 고려하면 여유가 작음
- 카메라가 실제 제공하는 YUYV는 2바이트/픽셀이며 고해상도·고프레임률에서 압축 필요성이 커짐
- 임베디드에서는 해상도와 프레임률이 곧 **CPU 부하와 전력 소비**

---

## V4L2란 (Video4Linux2)

- 리눅스의 표준 영상 입력 인터페이스. 웹캠은 `/dev/video0` 같은 **장치 파일**로 보임
- GPIO와 SPI가 그랬듯, 여기서도 조작은 전부 `ioctl`로 이루어짐

| ioctl                     | 하는 일                                     |
| ------------------------- | ------------------------------------------- |
| `VIDIOC_QUERYCAP`         | 이 장치가 캡처와 스트리밍을 지원하는지 확인 |
| `VIDIOC_S_FMT`            | 해상도와 픽셀 형식을 **협상**               |
| `VIDIOC_REQBUFS`          | 커널에 버퍼를 요청                          |
| `VIDIOC_QUERYBUF`         | 버퍼의 위치와 크기를 조회 → `mmap`          |
| `VIDIOC_QBUF` / `DQBUF`   | 빈 버퍼를 넣고, 채워진 버퍼를 꺼냄          |
| `VIDIOC_STREAMON` / `OFF` | 스트림 시작과 정지                          |

- 형식 역시 **협상** — 요청한 해상도를 드라이버가 바꿀 수 있으므로 반환값을 다시 읽음

---

## V4L2 - 버퍼 주고받기 (Streaming I/O)

- 프레임마다 복사하지 않기 위해 커널 버퍼를 `mmap`으로 **프로그램 주소 공간에 직접** 매핑

```text
   program                              driver
      |  QBUF (hand over an empty)  ->  |
      |                                 | camera fills it
      |  <- DQBUF (a filled buffer)     |
      |  ... use the frame ...          |
      |  QBUF (hand it back)        ->  |
```

- **돌려주지 않으면 파이프라인이 멈춤** — 그래서 예제의 `Grab()`은 다음 호출 때 이전 버퍼를 자동으로 반납하고, 반환한 포인터는 다음 `Grab()`까지만 유효
- 버퍼를 4개 쓰는 이유: 한 장을 처리하는 동안 다음 장이 채워지고 있어야 프레임이 끊기지 않음

---

## V4L2 - C270과 MJPEG (Why MJPEG)

- C270이 내주는 형식은 `YUYV`와 `MJPEG` 두 가지

| 형식            | 640×480 30fps 대역폭 | USB 2.0 (약 35MB/s) |
| --------------- | -------------------- | ------------------- |
| `YUYV` (무압축) | 약 18.4MB/s          | 아슬아슬하게 가능   |
| `MJPEG` (압축)  | 약 1~3MB/s           | 여유 있음           |
| `YUYV` 1280×720 | 약 55MB/s            | **불가능**          |

- 그래서 예제는 `MJPEG`를 요청 — 해상도를 올려도 대역폭이 감당됨
- 부수 효과 하나: **MJPEG 프레임은 그 자체로 완전한 JPEG 파일**
  - 사진 저장이 인코딩 없이 **바이트 복사**로 끝나는 이유

---

## 실습 08 - 구성과 빌드 (Layout and Build)

```text
project/
├── common/
│   ├── v4l2_capture.hpp       # RAII wrapper over V4L2 MJPEG capture
│   └── signal_stop.hpp
└── 12/src/
    ├── 02_photo_capture.cc
    └── 03_video_record.cc
```

```bash
cd project/12/src

# 3) Still photo -- Ctrl-C takes the picture
clang++ -std=c++14 -Wall -Wextra -I../../common \
        02_photo_capture.cc -o photo
./photo                        # Ctrl-C takes the photo

# 4) Video recorder
clang++ -std=c++14 -Wall -Wextra -I../../common \
        03_video_record.cc -o videorec
./videorec                     # Ctrl-C finalises the recording
```

- 두 예제 모두 **추가 라이브러리가 없음** — V4L2는 커널 인터페이스라 링크할 것이 없음

---

## 실습 08 - 사진 촬영 (Photo Capture)

- 신호가 올 때까지 프레임을 버리며 **노출과 화이트밸런스를 안정**시킴
- 버려지는 프레임은 낭비가 아님 — 켜자마자 찍은 사진은 어둡고 색이 틀어져 있음

[//]: # "INCLUDE: ./mep/12/src/02_photo_capture.cc --from 59 --to 71"

---

## 실습 08 - 셔터 (Taking the Shot)

- 신호를 받은 시점의 프레임은 **중간에 잘려 있는 경우**가 잦으므로, 온전한 것이 올 때까지 재시도

[//]: # "INCLUDE: ./mep/12/src/02_photo_capture.cc --from 73 --to 90"

---

## 실습 08 - 프레임 검증 (Validating the Frame)

- MJPEG 프레임이 곧 JPEG 파일이므로 **저장은 바이트 복사** — 인코딩 단계가 없음
- 그래서 잘린 프레임도 그대로 저장되어, **열리지 않는 파일**이 만들어짐

[//]: # "INCLUDE: ./mep/12/src/02_photo_capture.cc --from 24 --to 31"

- JPEG은 `FF D8`(SOI)로 시작해 `FF D9`(EOI)로 끝남 — 두 표지로 온전함을 판별
- USB 전송 오류로 프레임이 끊겨도 드라이버는 `bytesused > 0`으로 넘겨줌

---

## 실습 08 - AVI 컨테이너 (AVI Container)

- AVI 도 RIFF — WAV과 같은 구조가 한 단계 더 중첩된 형태

```text
RIFF 'AVI '
├── LIST 'hdrl'          header: resolution, frame count, playback rate
│   ├── avih
│   └── LIST 'strl' -> strh + strf
├── LIST 'movi'          frames stacked in order as '00dc' chunks
└── idx1                 index of each frame's offset and size
```

- 프레임 수와 전체 크기는 **녹화가 끝나야 알 수 있음** → 0으로 써 두고 나중에 되메움
- 재생 속도도 **측정해서** 기록 — 카메라가 24fps를 줬는데 30이라고 쓰면 재생이 빨라짐

---

## 실습 08 - 프레임 기록 (Writing Frames)

- 모든 청크는 **짝수 위치**에서 시작해야 하므로 길이가 홀수면 패딩 1바이트를 넣음

[//]: # "INCLUDE: ./mep/12/src/03_video_record.cc --from 107 --to 125"

---

## 실습 08 - 과제 (Tasks)

1. `./photo`를 실행하고 Ctrl-C로 사진을 찍어 `photo.jpg`를 확인
2. 카메라를 켜자마자 찍은 사진과 10초 뒤에 찍은 사진의 밝기를 비교
3. `./videorec`로 10초 분량을 녹화하고 재생 — 출력된 실측 fps를 기록
4. 해상도를 320×240, 640×480, 1280×720으로 바꾸며 CPU 사용률과 fps를 측정

### 실습 08 고찰 항목

- 해상도와 프레임률이 CPU 사용률에 미치는 영향을 표로 정리
- MJPEG와 무압축(YUYV)의 데이터량 차이를 실측
- 임베디드 장치에서 해상도를 결정할 때 고려해야 할 요소는

---

## 장치 접근의 공통 구조 (Device Access Pattern)

- 카메라와 마이크 모두 리눅스에서는 **장치 파일**로 접근

```text
open -> set the format (pixel format, resolution, sample rate)
     -> prepare buffers
     -> start streaming
     -> receive frames in a loop
     -> stop streaming -> close
```

| 장치   | 경로          | 인터페이스 |
| ------ | ------------- | ---------- |
| 카메라 | `/dev/video0` | V4L2       |
| 마이크 | `hw:1,0` 등   | ALSA       |

---

## 자주 겪는 문제 (Troubleshooting)

| 증상                      | 원인                           | 확인                          |
| ------------------------- | ------------------------------ | ----------------------------- |
| `Permission denied`       | `video`·`audio` 그룹 미포함    | `groups`                      |
| `Device or resource busy` | 다른 프로그램이 점유 중        | `fuser /dev/video0`           |
| 지원하지 않는 형식        | 장치가 그 조합을 제공하지 않음 | `v4l2-ctl --list-formats-ext` |
| 프레임 드롭               | USB 대역폭 부족, CPU 부하      | `top`, 해상도 낮추기          |
| 영상이 어둡거나 흔들림    | 자동 노출·화이트밸런스         | `v4l2-ctl --list-ctrls`       |

- 문제가 생기면 **먼저 명령줄 도구로 장치가 동작하는지 확인**한 뒤 코드를 의심할 것

---

## 12장 정리 (Summary)

- 멀티미디어는 센서 대비 데이터량이 **수천 배** 커서 대역폭과 CPU가 병목이 됨
- **오디오**: 표본화율 × 비트 심도 × 채널 이 초당 데이터량을 결정
  - 진폭(RMS)으로 소리 크기를 판정할 수 있음
- **영상**: 해상도 × 색 깊이 × 프레임률 — 무압축은 USB 대역폭을 쉽게 초과
  - 그래서 MJPEG·H.264 같은 **압축 형식**을 사용
- 장치는 **열기 → 형식 설정 → 스트리밍 → 닫기** 패턴으로 접근
- 해상도와 프레임률은 곧 **CPU 부하와 소비 전력** — 요구사항에 맞춰 최소로 설정
- 권한(`video`, `audio` 그룹)과 장치 점유가 오류의 주요 원인

> 다음 장에서는 지금까지의 코드를 타깃용으로 크로스 빌드함
