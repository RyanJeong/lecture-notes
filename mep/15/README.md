<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 6 - 사진과 영상 촬영

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 6 - 목표 (Goals)

- **프레임 수신**: V4L2 스트리밍 I/O로 USB 웹캠에서 영상 프레임을 연속으로 수신
- **사진 저장**: MJPEG 프레임 1장을 그대로 JPEG 파일로 저장
- **영상 녹화**: 연속 프레임을 이어 붙여 AVI 파일로 기록

| 프로그램              | 내용                              |
| --------------------- | --------------------------------- |
| `00_photo_capture.cc` | 온전한 프레임 1장을 사진으로 저장 |
| `01_video_record.cc`  | 연속 프레임을 AVI 파일로 기록     |

- **사용 API**: 영상 래퍼 없이 V4L2의 `ioctl()` 요청을 직접 호출
- **공용 헤더**: Ctrl-C 처리에 `signal_stop.hpp`만 사용(전체 코드는 9장 부록 참조)

---

## 실습 6 - 오디오 입력과의 차이 (What Changes)

| 구분      | 오디오(실습 5)                       | 영상(실습 6)                      |
| --------- | ------------------------------------ | --------------------------------- |
| 데이터 양 | 초당 32000바이트                     | 640×480 MJPEG 기준 초당 약 1MB    |
| 전달 방식 | 드라이버 버퍼에서 프로그램으로 **복사** | 드라이버 버퍼를 **매핑해 공유**   |
| 압축      | 사용하지 않음                        | 카메라가 MJPEG으로 압축해 전송    |
| 실패 양상 | 표본 손실(오버런)                    | 프레임이 **잘린 채** 도착         |

- **매핑(mapping)**: `mmap()`으로 드라이버 버퍼를 프로그램의 주소 공간에 연결해 복사 없이 읽는 방법
- **복사를 피하는 이유**: 프레임마다 수십 KB를 복사하면 CPU 시간과 메모리 대역폭을 소모

---

## 실습 6 - V4L2란 (Video4Linux2)

- **V4L2**: 리눅스 커널의 표준 영상 입출력 인터페이스
- **장치 파일**: 카메라는 `/dev/video0` 같은 문자 디바이스로 노출
- **`ioctl()`**: 장치 파일에 요청 코드와 구조체를 전달해 장치별 동작을 수행하는 시스템 콜
- **제어 방법**: `open()`으로 장치를 연 뒤 형식 설정과 버퍼 교환을 모두 `ioctl()` 요청으로 수행

| `ioctl()` 요청     | 동작                                          |
| ------------------ | --------------------------------------------- |
| `VIDIOC_S_FMT`     | 해상도와 픽셀 형식을 요청하고 실제 적용값 수신 |
| `VIDIOC_REQBUFS`   | 드라이버에 버퍼 할당 요청                     |
| `VIDIOC_QUERYBUF`  | 버퍼의 길이와 매핑용 오프셋 조회              |
| `VIDIOC_QBUF`      | 빈 버퍼를 드라이버의 입력 큐에 넣음           |
| `VIDIOC_DQBUF`     | 채워진 버퍼를 출력 큐에서 꺼냄                |
| `VIDIOC_STREAMON`  | 캡처 시작                                     |
| `VIDIOC_STREAMOFF` | 캡처 중지                                     |

---

## 실습 6 - 버퍼 주고받기 (Streaming I/O)

```text
program                          driver
   |  QBUF (empty buffer #0)  ->    |
   |  QBUF (empty buffer #1)  ->    |   fills them from the sensor
   |  <- DQBUF (full buffer #0)     |
   |  ... use the data ...          |
   |  QBUF (buffer #0 again)  ->    |
```

- **버퍼 소유**: 버퍼는 드라이버가 할당하며 프로그램은 `mmap()`으로 매핑해 읽기만 함
- **반환 누락 시**: 입력 큐에 빈 버퍼가 남지 않아 다음 `DQBUF`가 반환되지 않고 대기
- **유효 기간**: `DQBUF`로 꺼낸 버퍼의 내용은 다시 `QBUF` 하기 전까지만 유효

---

## 실습 6 - 왜 MJPEG인가 (Why MJPEG)

| 형식  | 640×480 프레임 1장             | 30fps 대역폭 |
| ----- | ------------------------------ | ------------ |
| YUYV  | 614400바이트(약 600KB)         | 약 18.4MB/s  |
| MJPEG | 약 20~40KB(장면에 따라 다름)   | 약 1MB/s     |

- **YUYV**: 픽셀 2개를 4바이트(밝기 Y 2개, 색차 U·V 각 1개)로 표현하는 비압축 형식, 픽셀당 2바이트
- **MJPEG(Motion JPEG)**: 프레임마다 독립된 JPEG 이미지로 압축하는 형식
- **사진 저장**: MJPEG 프레임 1장이 곧 완전한 JPEG 파일이므로 인코딩 없이 바이트 복사로 저장

---

## 실습 6 - 왜 MJPEG인가 (Cont'd - 1)

### USB 대역폭 (USB Bandwidth)

- **등시성(isochronous) 전송**: 일정 대역폭을 예약해 주기적으로 데이터를 보내는 USB 전송 방식
  - 예: 웹캠의 영상, USB 마이크의 오디오
- **엔드포인트(endpoint)**: USB 장치 내부에서 한 종류의 데이터를 주고받는 통로
- **USB 2.0 상한**: 등시성 엔드포인트 1개의 최대치는 1024바이트 × 3회 × 8000회/s = 약 24.6MB/s
- **YUYV 640×480 30fps**: 약 18.4MB/s로 상한의 약 75%를 차지
- **YUYV 1280×720 30fps**: 1280 × 720 × 2 × 30 = 약 55.3MB/s로 상한을 초과
- **MJPEG**: 640×480 30fps 기준 약 1MB/s로 YUYV의 약 18분의 1

---

## 실습 6 - 구성과 빌드 (Layout and Build)

```text
mep/
├── common/
│   └── signal_stop.hpp
└── lab06/
    ├── 00_photo_capture.cc
    └── 01_video_record.cc
```

```bash
cd mep/lab06
clang++ -std=c++14 -Wall -Wextra -I../common 00_photo_capture.cc -o photo
clang++ -std=c++14 -Wall -Wextra -I../common 01_video_record.cc -o videorec
```

- **링크 라이브러리 없음**: V4L2는 커널 인터페이스이고 `ioctl()`은 C 라이브러리에 포함되므로 `-l` 옵션 불필요
- **`v4l2-ctl --list-devices`**: 연결된 영상 장치와 `/dev/videoN` 경로를 나열(`v4l-utils` 패키지)
- **`v4l2-ctl -d /dev/video0 --list-formats-ext`**: 지원하는 픽셀 형식별 해상도와 프레임률을 나열

---

## 실습 6-A - 촬영 상수 (Capture Constants)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --to 22"

- **`g_buffers`, `g_lengths`**: 매핑한 버퍼의 주소와 길이, 종료 시 `munmap()`에 필요하므로 익명 네임스페이스에 보관

---

## 실습 6-A - 형식 협상 (Negotiating the Format)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 23 --to 36"

- **`VIDIOC_S_FMT`**: 요청을 드라이버에 전달하면 드라이버가 실제 적용값으로 구조체를 수정
- **결과 확인**: 카메라가 MJPEG을 지원하지 않으면 다른 형식으로 바뀌므로 `pixelformat`을 다시 비교
- **`V4L2_FIELD_ANY`**: 비월 주사(한 프레임을 홀수 줄과 짝수 줄로 나눠 전송) 여부를 드라이버에 맡김
- **한계**: 해상도도 바뀔 수 있으나 이 코드는 `pixelformat`만 확인

---

## 실습 6-A - 버퍼 요청 (Requesting Buffers)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 37 --to 47"

- **`V4L2_MEMORY_MMAP`**: 드라이버가 할당한 메모리를 프로그램이 매핑해 쓰는 방식
- **개수 확인**: 드라이버는 요청보다 적거나 많은 버퍼를 할당할 수 있음
  - 2개 미만: 프로그램이 버퍼를 읽는 동안 드라이버가 채울 버퍼가 없음
  - 4개 초과: `g_buffers` 배열의 범위를 벗어나므로 실패 처리

---

## 실습 6-A - 버퍼 매핑 (Mapping the Buffers)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 48 --to 63"

- **`VIDIOC_QUERYBUF`**: 버퍼 `i`의 길이(`length`)와 매핑용 오프셋(`m.offset`) 조회
- **`MAP_SHARED`**: 드라이버가 버퍼에 쓴 내용이 매핑한 주소에서 그대로 보임
- **`VIDIOC_QBUF`**: 매핑한 빈 버퍼를 입력 큐에 넣어 드라이버가 채울 수 있게 함

---

## 실습 6-A - 프레임 받기 (Grabbing a Frame)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 64 --to 74"

- **`VIDIOC_DQBUF`**: 채워진 버퍼 1개를 꺼내며, 블로킹 모드에서는 프레임이 도착할 때까지 대기
- **`bytesused`**: 실제 프레임 데이터의 길이, 버퍼 전체 크기(`length`)와 다름
- **반환값**: 꺼낸 버퍼의 번호(`index`), 실패하면 -1

---

## 실습 6-A - 버퍼 반환 (Requeueing a Buffer)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 75 --to 84"

- **`Requeue()`**: 다 쓴 버퍼를 `VIDIOC_QBUF`로 입력 큐에 다시 넣음
- **반환하지 않으면**: 버퍼 4개를 모두 꺼낸 뒤 다음 `VIDIOC_DQBUF`가 반환되지 않음

---

## 실습 6-A - 프레임 검증 (Validating the Frame)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 85 --to 93"

- **JPEG 표식**: JPEG 파일은 `FF D8`(SOI, Start of Image)로 시작해 `FF D9`(EOI, End of Image)로 끝남
- **잘린 프레임**: USB 전송 오류로 프레임이 끊겨도 드라이버는 `bytesused > 0`인 버퍼를 전달할 수 있음
- **검증하지 않으면**: 끝부분이 없는 JPEG 파일이 저장되어 이미지 뷰어에서 열리지 않음

---

## 실습 6-A - 캡처 시작 (Starting the Capture)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 94 --to 104"

- **시작 순서**: 장치 열기 → 신호 처리기 설치 → 형식 설정 → 버퍼 매핑 → `VIDIOC_STREAMON`
- **`VIDIOC_STREAMON`**: 입력 큐의 버퍼에 프레임을 채우기 시작하도록 캡처를 시작
- **실패 시**: 웹캠 연결 여부를 확인하도록 안내하고 종료

---

## 실습 6-A - 워밍업 (Warming Up)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 105 --to 117"

- **자동 노출(auto exposure)**: 장면 밝기에 맞춰 센서의 노출 시간을 조절하는 기능
- **화이트 밸런스(white balance)**: 조명 색과 무관하게 흰 물체가 흰색으로 찍히도록 색 비율을 보정하는 기능
- **워밍업**: 두 기능이 안정될 때까지 Ctrl-C 전의 프레임을 받아 버림
- **워밍업이 없으면**: 첫 프레임이 어둡거나 색이 틀어질 수 있음(과제 2에서 비교)

---

## 실습 6-A - 셔터 (Taking the Shot)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 118 --to 132"

- **재시도**: SOI와 EOI를 모두 갖춘 프레임이 올 때까지 최대 15프레임 시도
- **불합격 버퍼 반환**: 반환하지 않으면 4회 실패 후 입력 큐가 비어 `VIDIOC_DQBUF`가 반환되지 않음
- **합격 버퍼**: 저장이 끝날 때까지 반환하지 않으므로 드라이버가 내용을 덮어쓰지 않음

---

## 실습 6-A - 저장과 정리 (Saving and Cleanup)

[//]: # "INCLUDE: ./mep/15/src/00_photo_capture.cc --from 133"

- **바이트 복사**: MJPEG 프레임은 그 자체가 완전한 JPEG이므로 `fwrite()` 한 번으로 저장
- **정리**: `VIDIOC_STREAMOFF`로 캡처를 멈춘 뒤 `munmap()`, `close()` 순서로 자원 해제

---

## 실습 6-B - AVI 컨테이너 (AVI Container)

- **AVI(Audio Video Interleave)**: RIFF 형식의 영상 파일, 실습 5의 WAV와 같은 청크가 한 단계 더 중첩
- **LIST 청크**: 다른 청크를 담는 청크이며, 크기 뒤에 4바이트 목록 이름(`hdrl`, `movi` 등)이 옴

```text
RIFF "AVI "
├── LIST "hdrl"        headers
│   ├── "avih"         main header: us per frame, frame count, size
│   └── LIST "strl"    one stream
│       ├── "strh"     stream header: MJPG, frame rate, length
│       └── "strf"     stream format: width, height, compression
├── LIST "movi"        the frames themselves
│   └── "00dc" ...     one chunk per frame
└── "idx1"             index: offset and size of every frame
```

- **`00dc`**: 스트림 0번의 압축 영상(compressed video) 프레임을 담는 청크
- **크기 필드 문제**: 크기와 프레임 수는 녹화가 끝나야 알 수 있으므로 0으로 기록한 뒤 마지막에 되메움

---

## 실습 6-B - 헤더 작성 (Writing the Header)

[//]: # "INCLUDE: ./mep/15/src/01_video_record.cc --from 110 --to 122 --no-comment"

- **`ftell()`**: 현재 파일 위치를 반환하며, 나중에 되메울 크기 필드의 위치를 저장하는 데 사용
- **`riff_size_pos_`, `avih_pos_`**: RIFF 크기 필드와 `avih` 본문의 시작 위치
- **`hdrl` 크기**: 하위 청크의 크기가 고정이므로 4 + 8 + 56 + 4 + 8 + 8 + 56 + 8 + 40 = 192바이트를 미리 기록

---

## 실습 6-B - 프레임 기록 (Writing Frames)

[//]: # "INCLUDE: ./mep/15/src/01_video_record.cc --from 173 --to 191 --no-comment"

- **청크 구성**: `00dc` 태그, 4바이트 크기, JPEG 데이터 순서로 기록
- **패딩**: RIFF 청크는 짝수 위치에서 시작하므로 홀수 길이 프레임 뒤에 1바이트를 추가하며 크기에는 포함하지 않음
- **인덱스 정보**: 프레임의 위치(`movi` 태그 기준)와 크기를 `index_`, `sizes_`에 보관

---

## 실습 6-B - 인덱스와 되메우기 (Index and Patching)

[//]: # "INCLUDE: ./mep/15/src/01_video_record.cc --from 195 --to 207 --no-comment"

- **`idx1` 항목**: 프레임마다 태그, 플래그, 위치, 크기의 4개 필드(16바이트)를 기록
- **`AVIIF_KEYFRAME`**: 다른 프레임 없이 단독으로 디코딩할 수 있는 프레임임을 나타내는 플래그
  - MJPEG은 모든 프레임이 독립된 JPEG이므로 모든 항목에 설정
- **인덱스의 역할**: 재생 프로그램이 파일 전체를 읽지 않고 원하는 프레임 위치로 바로 이동

---

## 실습 6-B - 프레임률은 측정값 (Measured, Not Assumed)

[//]: # "INCLUDE: ./mep/15/src/01_video_record.cc --from 211 --to 227 --no-comment"

- **측정 프레임률**: 녹화한 프레임 수 ÷ 실제 녹화 시간
- **예**: 10초 동안 240프레임(24fps)을 받고 파일에 30fps로 기록하면 8초 만에 재생이 끝남
- **`avih` 되메우기**: 프레임 간격(μs), 총 프레임 수, 최대 프레임 크기
- **`strh` 되메우기**: `strh_pos_`부터 24바이트 위치의 프레임률, 32바이트 위치의 길이, 36바이트 위치의 권장 버퍼 크기

---

## 실습 6-B - 녹화 루프 (Recording Loop)

[//]: # "INCLUDE: ./mep/15/src/01_video_record.cc --from 280 --to 293 --no-comment"

- **루프 순서**: `Grab()`으로 프레임을 꺼냄 → `WriteFrame()`으로 기록 → `Requeue()`로 버퍼 반환
- **진행 출력**: 15프레임마다 누적 프레임 수와 경과 시간을 같은 줄에 갱신
- **`CLOCK_MONOTONIC`**: 시스템 시각을 변경해도 거꾸로 가지 않는 시계이므로 경과 시간 측정에 사용

---

## 실습 6-B - 마감 (Finalising)

[//]: # "INCLUDE: ./mep/15/src/01_video_record.cc --from 297 --to 310 --no-comment"

- **녹화 시간**: 루프를 빠져나온 시점까지의 경과 시간을 `Finalise()`에 전달해 프레임률 계산
- **마감 순서**: `VIDIOC_STREAMOFF` → 인덱스 기록과 크기 되메우기 → `munmap()`, `close()`
- **마감 누락 시**: `kill -9`처럼 신호 처리기를 거치지 않고 종료하면 인덱스가 없고 크기 필드가 0인 파일이 남음

---

## 실습 6 - 확인 방법 (Checking It Works)

```bash
v4l2-ctl --list-devices                      # expect /dev/video0
v4l2-ctl -d /dev/video0 --list-formats-ext   # confirm MJPG is offered

./photo                      # Ctrl-C takes the picture
file photo.jpg               # expect "JPEG image data"

./videorec                   # Ctrl-C finalises the recording
ffplay record.avi
```

| 증상               | 원인                     | 조치                              |
| ------------------ | ------------------------ | --------------------------------- |
| 장치 열기 실패     | 권한 부족 또는 미연결    | `video` 그룹 가입, USB 연결 확인  |
| MJPEG 거부         | 카메라가 지원하지 않음   | `--list-formats-ext`로 형식 확인  |
| 사진이 열리지 않음 | 잘린 프레임 저장         | SOI/EOI 검증 동작 확인            |

---

## 실습 6 - 과제 (Tasks)

1. 사진을 촬영하고 `file photo.jpg`로 JPEG 형식인지 확인
2. 워밍업 없이 실행 직후 Ctrl-C를 눌러 촬영한 사진과 충분히 기다린 사진의 색과 밝기를 비교
3. 10초를 녹화한 뒤 프로그램이 출력한 fps와 `ffprobe record.avi`가 보고하는 값을 비교
4. 해상도를 1280×720으로 바꿔 프레임 크기와 fps의 변화를 기록
5. 녹화 중 `kill -9`로 강제 종료하고, 정상 마감한 파일과 재생 결과를 비교

### 고찰 항목

- 버퍼를 복사하지 않고 매핑해 쓰는 이유는 무엇인가
- 프레임률을 측정하지 않고 30으로 고정하면 무엇이 잘못되는가
- 잘린 프레임을 걸러 내지 않으면 어떤 증상으로 나타나는가
