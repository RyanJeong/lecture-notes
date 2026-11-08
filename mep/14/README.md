<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 5 - 오디오 시각화와 녹음

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 5 - 목표 (Goals)

- **표본 수집**: USB 마이크에서 PCM 표본을 연속으로 읽는 과정을 직접 구현
- **레벨 미터**: 표본의 세기를 계산해 터미널에 막대 그래프로 출력
- **녹음**: 수집한 표본을 WAV 파일로 저장하고 `aplay`로 재생해 확인

| 프로그램                 | 내용                                   |
| ------------------------ | -------------------------------------- |
| `00_audio_visualizer.cc` | 입력 레벨을 dBFS 값과 막대 그래프로 출력 |
| `01_wav_record.cc`       | Ctrl-C를 누를 때까지 WAV 파일로 녹음   |

- **사용 API**: 오디오 래퍼 없이 ALSA 라이브러리 함수를 직접 호출
- **공용 헤더**: Ctrl-C 처리에 `signal_stop.hpp`만 사용(전체 코드는 9장 부록 참조)

---

## 실습 5 - 센서 입력과의 차이 (What Changes)

| 구분        | 센서(실습 3~4)                  | 오디오(실습 5)                      |
| ----------- | ------------------------------- | ----------------------------------- |
| 데이터 양   | 측정 1회당 수 바이트            | 초당 16000 표본(32000바이트)        |
| 읽는 시점   | 프로그램이 정함                 | **장치의 표본화 주파수**가 정함     |
| 늦게 읽으면 | 측정 시점이 늦어질 뿐 손실 없음 | 버퍼가 넘쳐 **표본 손실**(오버런)   |
| 버퍼        | 불필요                          | 커널 드라이버가 표본을 버퍼에 누적  |

- **오버런(overrun)**: 표본이 쌓이는 속도를 읽기가 따라가지 못해 드라이버 버퍼가 가득 찬 상태
- **핵심 차이**: 프로그램이 원할 때 읽는 방식에서 장치의 속도에 맞춰 읽는 방식으로 전환

---

## 실습 5 - PCM 기초 (Pulse Code Modulation)

- **PCM**: 아날로그 신호를 일정 간격으로 측정하고 각 측정값을 정수로 바꿔 나열하는 디지털 표현
- **표본(sample)**: 한 시점에 측정한 신호의 크기를 나타내는 정수 1개

| 용어          | 뜻                          | 이 실습의 값          |
| ------------- | --------------------------- | --------------------- |
| 표본화 주파수 | 1초당 측정 횟수             | 16000Hz               |
| 비트 깊이     | 표본 1개를 표현하는 비트 수 | 16비트 부호 있는 정수 |
| 채널          | 동시에 측정하는 신호의 수   | 1(모노)               |

- **표본 범위**: 16비트 부호 있는 정수이므로 -32768 ~ 32767
- **데이터 양**: 16000Hz × 2바이트 × 1채널 = 초당 32000바이트

---

## 실습 5 - PCM 기초 (Cont'd - 1)

### 프레임과 버퍼 (Frames and Buffers)

- **프레임(frame)**: 한 시점의 모든 채널 표본 묶음, 모노에서는 표본 1개(2바이트)
  - ALSA 함수의 크기 전달인자와 반환값은 바이트가 아닌 프레임 단위
- **링 버퍼(ring buffer)**: 드라이버가 수집한 프레임을 프로그램이 읽을 때까지 보관하는 원형 버퍼
- **주기(period)**: 하드웨어가 링 버퍼를 채우다가 인터럽트로 프로그램을 깨우는 프레임 수 단위
- **지연 시간(latency)**: 링 버퍼 전체가 담는 시간, 이 실습에서는 100ms(`kLatencyUs`)
- **읽기 단위**: `snd_pcm_readi()` 1회에 1024프레임(`kPeriod`), 1024 / 16000 = 64ms
  - 코드의 `kPeriod`는 읽기 단위이며, ALSA 주기는 `snd_pcm_set_params()`가 지연 시간을 기준으로 정함

---

## 실습 5 - ALSA란 (Advanced Linux Sound Architecture)

- **ALSA**: 리눅스의 표준 오디오 시스템, 커널 드라이버와 사용자 라이브러리로 구성
  - **커널 드라이버**: 오디오 장치를 `/dev/snd/pcmC3D0c` 같은 장치 파일로 노출(카드 3, 장치 0, 녹음)
  - **`libasound`**: 장치 파일 대신 `snd_pcm_*()` 함수로 장치에 접근하게 하는 사용자 라이브러리
- **장치 이름**: `hw:<카드>,<장치>` 또는 `plughw:<카드>,<장치>` 형식

| 이름     | 동작                                                         |
| -------- | ------------------------------------------------------------ |
| `hw`     | 장치가 지원하는 형식만 허용하며, 다르면 설정이 실패          |
| `plughw` | 형식, 표본화 주파수, 채널 수가 다르면 `plug` 플러그인이 변환 |

- **예**: 48000Hz만 지원하는 마이크에 16000Hz를 요청하면 `hw`는 실패, `plughw`는 변환하여 성공
- **실습의 선택**: 마이크마다 지원 형식이 다르므로 `plughw` 사용

---

## 실습 5 - 장치 지정 (Selecting the Device)

```text
$ arecord -l
**** List of CAPTURE Hardware Devices ****
card 3: U0x46d0x825 [USB Device 0x46d:0x825], device 0: USB Audio [USB Audio]
```

- **`arecord -l`**: 연결된 녹음 장치의 카드 번호와 장치 번호를 나열하는 명령
- **읽는 법**: 위 출력은 카드 `3`, 장치 `0`이므로 전달인자는 **`plughw:3,0`**

```bash
./visualizer plughw:3,0
./wavrec plughw:3,0
```

- **기본값**: 전달인자를 생략하면 코드에 지정한 `plughw:1,0` 사용
- **번호 변동**: 카드 번호는 부팅 시 장치를 인식한 순서로 정해지므로 실행 전 `arecord -l`로 다시 확인

---

## 실습 5 - 장치 설정 방법 (Two Ways to Configure)

- **하드웨어 파라미터**: 형식, 채널 수, 표본화 주파수, 버퍼 크기처럼 녹음 전에 정해야 하는 값
- **협상**: 장치가 지원하지 않는 값은 가장 가까운 지원 값으로 바뀌거나 설정이 실패

| 방법                    | 호출 횟수    | 용도                                                 |
| ----------------------- | ------------ | ---------------------------------------------------- |
| `snd_pcm_set_params()`  | 1회          | 형식, 주파수 같은 기본 항목만 정하면 되는 경우       |
| `snd_pcm_hw_params_*()` | 항목마다 1회 | 주기·버퍼 크기를 직접 정하고 실제 적용값을 확인할 때 |

- **실습의 선택**: 설정 항목이 고정되어 있으므로 `snd_pcm_set_params()` 사용

---

## 실습 5 - 장치 설정 방법 (Cont'd - 1)

### `snd_pcm_set_params()`의 전달인자

| 전달인자        | 실습의 값                       | 의미                                         |
| --------------- | ------------------------------- | -------------------------------------------- |
| `format`        | `SND_PCM_FORMAT_S16_LE`         | 16비트 부호 있는 정수, 리틀 엔디언           |
| `access`        | `SND_PCM_ACCESS_RW_INTERLEAVED` | `snd_pcm_readi()`로 읽으며 채널을 교대로 배치 |
| `channels`      | `1`                             | 모노                                         |
| `rate`          | `16000`                         | 표본화 주파수(Hz)                            |
| `soft_resample` | `1`                             | 지원하지 않는 주파수의 소프트웨어 변환 허용  |
| `latency`       | `100000`                        | 요구 지연 시간(μs), 링 버퍼 길이의 기준      |

- **반환값**: 성공하면 0, 실패하면 음수 오류 코드
- **오류 메시지**: `snd_strerror(rc)`로 오류 코드를 문자열로 변환

---

## 실습 5 - 구성과 빌드 (Layout and Build)

```text
mep/
├── common/
│   └── signal_stop.hpp
└── lab05/
    ├── 00_audio_visualizer.cc
    └── 01_wav_record.cc
```

```bash
cd mep/lab05
clang++ -std=c++14 -Wall -Wextra -I../common \
        00_audio_visualizer.cc -o visualizer -lasound
clang++ -std=c++14 -Wall -Wextra -I../common \
        01_wav_record.cc -o wavrec -lasound
```

- **`-lasound`**: 빠뜨리면 `snd_pcm_open` 등에 대한 `undefined reference` 링크 오류 발생
- **`-I../common`**: `signal_stop.hpp`를 찾기 위한 헤더 검색 경로
- **불필요한 항목**: GPIO를 사용하지 않으므로 `gpio.hpp`와 `-lgpiod`는 불필요

---

## 실습 5-A - 녹음 상수 (Capture Constants)

[//]: # "INCLUDE: ./mep/14/src/00_audio_visualizer.cc --to 18"

- **`kRate`**: 16000Hz 표본화는 그 절반인 8000Hz까지의 소리 성분을 표현
- **`kPeriod`**: 1024프레임마다 막대를 갱신하므로 갱신 간격은 64ms
- **`kFloorDb`**: -60dBFS보다 작은 값은 무음으로 간주

---

## 실습 5-A - 진폭 계산 (Amplitude)

- **평균의 문제**: 0을 중심으로 진동하는 파형은 양수와 음수가 상쇄되어 평균이 0에 가까움
- **RMS(Root Mean Square, 제곱평균제곱근)**: 표본을 제곱해 평균한 뒤 제곱근을 취한 신호 세기

$$\text{RMS} = \sqrt{\frac{1}{N}\sum_{i=1}^{N} x_i^2}$$

- **예**: +1000과 -1000이 번갈아 나오는 파형은 평균 0, RMS 1000

[//]: # "INCLUDE: ./mep/14/src/00_audio_visualizer.cc --from 19 --to 27"

---

## 실습 5-A - 데시벨로 바꾸기 (Decibels)

[//]: # "INCLUDE: ./mep/14/src/00_audio_visualizer.cc --from 28 --to 35"

- **dBFS(decibels relative to full scale)**: 최대 크기 32768을 0dB로 두고 그 아래를 음수로 나타내는 단위
  - 계산식: dBFS = 20 log₁₀(RMS / 32768), 예: RMS 3277 → -20dBFS
- **로그 눈금의 필요성**: 청각은 소리 세기를 비율로 인지하므로 선형 눈금으로는 작은 소리를 구분하지 못함
- **비교**: 50칸 막대에서 RMS 328은 선형 눈금으로 0칸, dBFS 눈금(-40dBFS)으로 16칸

---

## 실습 5-A - 장치 열기 (Opening the Device)

[//]: # "INCLUDE: ./mep/14/src/00_audio_visualizer.cc --from 36 --to 53"

- **`SND_PCM_STREAM_CAPTURE`**: 녹음 방향으로 장치를 열며, 마지막 전달인자 0은 블로킹 모드
- **블로킹 모드**: `snd_pcm_readi()`가 요청한 프레임이 모일 때까지 반환하지 않음
- **오류 처리**: 장치 열기, 설정, 신호 처리기 설치 중 하나라도 실패하면 장치 지정 방법을 안내하고 종료

---

## 실습 5-A - 오버런과 복구 (Overruns)

[//]: # "INCLUDE: ./mep/14/src/00_audio_visualizer.cc --from 54 --to 64"

- **오버런 발생 시**: `snd_pcm_readi()`가 `-EPIPE` 반환
- **`snd_pcm_recover()`**: 스트림을 다시 준비 상태로 만들어 녹음을 재개
  - 세 번째 전달인자 1: 복구 시 오류 메시지 출력 생략
- **복구 후 계속**: 손실 구간은 짧은 공백으로 남을 뿐이므로 프로그램을 종료하지 않음
- **복구 실패 시**: 장치 분리처럼 복구할 수 없는 오류이므로 루프 종료

---

## 실습 5-A - 막대 그리기 (Drawing the Bar)

[//]: # "INCLUDE: ./mep/14/src/00_audio_visualizer.cc --from 65"

- **막대 길이**: -60dBFS를 0칸, 0dBFS를 50칸으로 두고 선형 변환
- **`\r`**: 줄을 바꾸지 않고 커서를 줄 맨 앞으로 옮겨 같은 줄에 다시 출력
- **`std::fflush(stdout)`**: 터미널 출력은 줄 단위로 버퍼링되므로 `\n` 없는 출력을 즉시 화면에 반영

---

## 실습 5-B - WAV 파일 구조 (WAV Container)

- **RIFF(Resource Interchange File Format)**: 4바이트 ID, 4바이트 크기, 내용으로 된 청크(chunk)를 이어 붙인 파일 형식
- **WAV**: RIFF 형식의 한 종류, PCM WAV는 44바이트 헤더 뒤에 표본을 그대로 이어 붙임
- **리틀 엔디언(little endian)**: 다중 바이트 정수의 최하위 바이트를 낮은 주소에 먼저 저장하는 순서
  - 예: 16000 = `0x00003E80` → 파일에 `80 3E 00 00` 순서로 기록
- **크기 필드 문제**: RIFF 크기와 `data` 크기는 녹음이 끝나야 알 수 있음

---

## 실습 5-B - WAV 파일 구조 (Cont'd - 1)

### 44바이트 헤더 (44-Byte Header)

```text
offset size field            value in this lab
0      4    "RIFF"
4      4    RIFF size        36 + data size (patched at the end)
8      4    "WAVE"
12     4    "fmt "           chunk ID with a trailing space
16     4    fmt size         16
20     2    audio format     1 (PCM)
22     2    channels         1
24     4    sample rate      16000
28     4    byte rate        32000 (sample rate x block align)
32     2    block align      2 (channels x bits / 8)
34     2    bits per sample  16
36     4    "data"
40     4    data size        sample bytes (patched at the end)
44     ...  samples
```

- **RIFF 크기**: 파일 전체 크기에서 앞 8바이트(`RIFF` ID와 크기 필드)를 뺀 값

---

## 실습 5-B - 녹음 상수 (Capture Constants)

[//]: # "INCLUDE: ./mep/14/src/01_wav_record.cc --to 18"

- **`kChannels`, `kBits`**: WAV 헤더의 채널 수와 비트 깊이 필드에 그대로 기록
- **`kHeaderBytes`**: RIFF 크기 계산(44 - 8 + 데이터 크기)에 사용
- **`kOutPath`**: 현재 디렉터리의 `record.wav`에 저장하며, 같은 이름의 파일이 있으면 덮어씀

---

## 실습 5-B - 바이트 단위로 쓰기 (Little Endian)

[//]: # "INCLUDE: ./mep/14/src/01_wav_record.cc --from 19 --to 34"

- **바이트 단위 기록**: `value & 0xFF`로 최하위 바이트를 꺼내 먼저 기록하므로 호스트와 무관하게 리틀 엔디언
- **정수를 통째로 쓰는 경우**: `fwrite(&value, 4, 1, file)` 호출은 메모리의 바이트 순서를 그대로 기록
  - 예: 빅 엔디언 호스트에서는 16000이 `00 00 3E 80` 순서로 기록
- **표본 데이터**: ALSA가 `S16_LE` 형식의 바이트열을 전달하므로 변환 없이 그대로 기록

---

## 실습 5-B - 헤더 구성 (Header Layout)

[//]: # "INCLUDE: ./mep/14/src/01_wav_record.cc --from 35 --to 47"

- **`align`**: 프레임 1개의 바이트 수, 1채널 × 16비트 / 8 = 2
- **`kRate * align`**: 초당 바이트 수, 16000 × 2 = 32000
- **`WriteU32(file, 16)`, `WriteU16(file, 1)`**: `fmt ` 청크 크기 16과 형식 코드 1(PCM)
- **`&&` 연결**: 쓰기가 한 번이라도 실패하면 이후 쓰기를 생략하고 `false` 반환

---

## 실습 5-B - 장치와 파일 열기 (Opening Device and File)

[//]: # "INCLUDE: ./mep/14/src/01_wav_record.cc --from 48 --to 64"

- **임시 헤더**: 데이터 크기를 모르므로 `data_bytes`를 0으로 둔 헤더를 먼저 기록
- **기록 위치**: 헤더를 쓴 뒤 파일 위치가 44바이트이므로 표본이 헤더 바로 뒤에 이어짐
- **오류 처리**: 장치 열기부터 임시 헤더 기록까지 한 단계라도 실패하면 종료

---

## 실습 5-B - 녹음 루프 (Recording Loop)

[//]: # "INCLUDE: ./mep/14/src/01_wav_record.cc --from 65 --to 81"

- **기록 크기**: 읽은 프레임 수 × 2바이트(`sizeof(std::int16_t)`)
- **녹음 시간**: `data_bytes / (16000 × 2)`초를 같은 줄에 갱신하여 출력
- **쓰기 실패 시**: 디스크 공간 부족 등으로 기록한 바이트 수가 다르면 루프 종료

---

## 실습 5-B - 크기 필드 되메우기 (Patching the Sizes)

[//]: # "INCLUDE: ./mep/14/src/01_wav_record.cc --from 82"

- **정상 종료 경로**: Ctrl-C(SIGINT)가 정지 플래그를 설정하면 루프를 빠져나와 마감 처리를 수행
- **되메우기**: `fseek()`로 파일 처음으로 돌아가 실제 `data_bytes`로 헤더 44바이트를 다시 기록
- **되메우기 누락 시**: 두 크기 필드가 0으로 남아 재생 프로그램이 데이터 길이를 0바이트로 해석
- **한계**: `kill -9`로 보내는 SIGKILL은 신호 처리기를 거치지 않으므로 헤더가 갱신되지 않음

---

## 실습 5 - 확인 방법 (Checking It Works)

```bash
arecord -l                      # find the card and device numbers
./visualizer plughw:3,0         # speak and watch the bar move
./wavrec plughw:3,0             # Ctrl-C finalises the file
aplay record.wav                # play it back
```

| 증상                 | 원인             | 조치                                   |
| -------------------- | ---------------- | -------------------------------------- |
| 장치 열기 실패       | 카드 번호가 다름 | `arecord -l` 확인 후 전달인자 지정     |
| 막대가 움직이지 않음 | 입력 음량이 0    | `alsamixer`에서 캡처 볼륨 조절         |
| 재생 길이가 0        | 크기 필드 미갱신 | Ctrl-C로 종료했는지 확인               |

---

## 실습 5 - 과제 (Tasks)

1. 비주얼라이저를 실행해 조용할 때와 말할 때의 dBFS 값을 기록
2. `kRate`를 8000Hz와 44100Hz로 바꿔 같은 시간 동안 녹음한 파일의 크기를 비교
3. 16kHz WAV의 표본은 그대로 두고 헤더의 표본화 주파수·초당 바이트 수만 32kHz·8kHz로 바꿔 재생
   - 헤더만 바꾸면 재생 속도와 음높이가 함께 2배 또는 0.5배로 바뀜
   - 표본 자체를 다시 표본화(리샘플링)하면 재생 속도와 음높이를 유지할 수 있음
4. `timeout -s INT 5 ./wavrec plughw:3,0`으로 5초를 녹음해 파일 크기를 `16000 × 2 × 5 + 44 = 160044`바이트와 비교
   - 표본은 1024프레임(2048바이트) 단위로 기록되므로 정확히 일치하지 않음

---

## 실습 5 - 과제 (Cont'd - 1)

5. 녹음 중 Ctrl-Z로 프로그램을 일시 정지한 뒤 `fg`로 재개해 오버런을 유발하고 복구 동작을 관찰
   - `snd_pcm_recover()`의 세 번째 전달인자를 0으로 바꾸면 복구 시 메시지 출력
6. 실습 6의 MJPEG 프레임을 JPEG 디코더로 RGB 픽셀로 변환한 뒤 흑백 사진으로 저장
   - 카메라의 캡처 형식(MJPEG)은 변경하지 않음
   - 밝기는 RGB 단순 평균이 아닌 `Gray = 0.299R + 0.587G + 0.114B`로 계산
   - PGM은 픽셀마다 밝기 값 1개를 저장하고, 흑백 JPEG은 R·G·B에 같은 밝기 값을 넣어 다시 인코딩

### 고찰 항목

- 평균 대신 RMS를 쓰는 이유는 무엇인가
- 오버런을 오류로 처리해 프로그램을 종료했다면 어떤 문제가 생기는가
- 크기 필드를 녹음 시작 시점에 알 수 없는 파일 구조의 장단점은 무엇인가
