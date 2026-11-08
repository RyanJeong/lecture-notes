<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 7 - 웹캠 기반 CCTV

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 7 - 무엇을 만드는가 (What It Is)

- **정의**: USB 웹캠 영상에서 물체를 검출하고 결과를 **웹 페이지로 제공**하는 소형 CCTV
- **저장소**: [github.com/RyanJeong/mep-cctv](https://github.com/RyanJeong/mep-cctv)

| 구성 요소   | 내용                                                  |
| ----------- | ----------------------------------------------------- |
| 객체 검출   | YOLOv8n이 찾은 물체에 클래스명과 신뢰도를 사각형으로 표시 |
| 음향 감지   | 평균을 뺀 RMS로 소리 유무 판단(신경망 모델 아님)      |
| 결과 화면   | HTTP로 MJPEG 스트림 전송, 브라우저의 `<img>` 태그로 재생 |
| 호스트 지표 | 프로세스 CPU 사용률, 상주 메모리, CPU 온도를 1초마다 갱신 |

- **목표**: CCTV 자체가 아니라 **같은 모델을 두 방식으로 배포해 비용을 측정**

---

## 실습 7 - 용어 정리 (Key Terms)

- **객체 검출(object detection)**: 영상에서 물체의 종류와 위치(사각형)를 찾는 작업
- **YOLOv8n**: Ultralytics의 객체 검출 모델 YOLOv8 중 가장 작은(nano) 버전
  - COCO 데이터셋의 80개 클래스(사람, 자동차, 컵 등)를 검출
- **신뢰도(confidence)**: 검출 결과가 맞을 가능성으로 모델이 출력하는 0~1 사이의 값
- **가중치(weights)**: 학습으로 정해진 모델의 수치 매개변수, YOLOv8n은 약 320만 개
- **추론(inference)**: 학습이 끝난 모델에 입력을 넣어 결과를 계산하는 과정

---

## 실습 7 - 용어 정리 (Cont'd - 1)

- **ONNX(Open Neural Network Exchange)**: 모델의 연산 그래프와 가중치를 저장하는 표준 파일 형식(`.onnx`)
- **ONNX Runtime**: `.onnx` 파일을 읽어 추론을 수행하는 Microsoft의 라이브러리
- **TVM(Apache TVM)**: 모델 그래프를 특정 CPU용 기계어 코드로 컴파일하는 딥러닝 컴파일러
- **연산 커널(kernel)**: 합성곱처럼 연산 하나를 수행하도록 생성된 함수(운영체제 커널과 다름)
- **아티팩트(artifact)**: 빌드 결과로 만들어져 장치에 복사하는 파일 묶음(실행 파일, 라이브러리, 웹 자원)

---

## 실습 7 - 앞선 실습이 모두 등장 (Everything Returns)

| 이 프로젝트의 요소      | 배운 곳 |
| ----------------------- | ------- |
| 도커 크로스 컴파일      | 실습 1  |
| 공유 상태와 스레드 분리 | 실습 4  |
| HTTP로 결과 내보내기    | 실습 4  |
| ALSA 오디오 캡처와 RMS  | 실습 5  |
| V4L2 MJPEG 캡처         | 실습 6  |
| 전력·발열과 스로틀링    | 1·2장   |

- **새 요소**: 모델 관리(변환과 튜닝)와 배포 자동화(CI/CD) 두 가지

---

## 실습 7 - 시스템 구성 (Architecture)

```text
USB webcam --V4L2--> capture --> detector (YOLOv8n) --> annotator
                                     |                      |
USB mic ----ALSA---> energy check    |                  JPEG encode
                                     v                      v
                              host metrics  ------->  HTTP server
                                                            |
                                            browser <--MJPEG stream
```

- **스레드 분리**: 캡처·추론·전송의 주기가 서로 다르므로 실습 4와 같은 구조로 분리
- **사각형 일치**: 사각형을 프레임에 그린 뒤 JPEG으로 인코딩하므로 영상과 사각형이 항상 일치
  - 좌표를 따로 보내 브라우저가 그리면 영상과 좌표의 도착 시점이 달라 어긋날 수 있음

---

## 실습 7 - 두 가지 모드 (Two Modes)

- **공통**: 같은 C API(`include/cctv/cctv.h`), 같은 공유 라이브러리(`libcctv`), 같은 모델, 같은 입력 크기
- **차이**: 모델을 실행하는 방법 하나뿐

| 모드     | 빌드 옵션            | 파이에 복사하는 파일                              |
| -------- | -------------------- | ------------------------------------------------- |
| `onnx`   | `-DCCTV_MODE=onnx`   | `libcctv.so` + ONNX Runtime 라이브러리 + `.onnx`  |
| `native` | `-DCCTV_MODE=native` | `libcctv.so` **하나**(TVM 런타임 정적 링크)       |

- **`onnx`**: 런타임 12MB와 모델 파일 12MB가 장치에 **따로** 필요
- **`native`**: TVM이 생성한 연산 커널과 가중치가 `libcctv.so` 안에 들어감

---

## 실습 7 - 모델을 코드로 포팅하기 (Model to Code)

| 관점      | 추론 런타임 방식(`onnx`)              | 코드 컴파일 방식(`native`)        |
| --------- | ------------------------------------- | --------------------------------- |
| 배포 단위 | 런타임 + 모델 파일                    | 라이브러리 하나                   |
| 실행 방식 | 런타임이 그래프를 읽어 연산별 커널 호출 | 그래프 전체를 미리 **기계어**로 변환 |
| 의존성    | 런타임 버전에 묶임                    | 별도 설치 없음                    |
| 디스크    | 약 24MB 추가                          | 추가 없음                         |

- **배포 단순화**: 장치에 설치할 런타임이 없으므로 런타임 버전 충돌이 생기지 않음
- **실습 1과의 관계**: 호스트에서 만든 결과물을 복사만 하면 되는 크로스 컴파일과 같은 논리

---

## 실습 7 - 측정 결과 (Measured on a Pi 4)

| 모드     | 평균 fps | 관측 범위 | 프레임당 |
| -------- | -------- | --------- | -------- |
| `onnx`   | 6.13     | 5.96~6.29 | 163ms    |
| `native` | 5.97     | 5.76~6.11 | 168ms    |

- **측정 조건**: Raspberry Pi 4 Model B(4GB), 640×480 USB 카메라
- **측정 범위**: 캡처, 추론, 사각형 그리기, JPEG 인코딩을 모두 포함한 파이프라인 fps
- **표본**: 모드마다 2회 실행에서 얻은 `/status` 값 10개의 평균(저장소에 기록된 과거 측정값)
- **결과**: 코드로 컴파일한 모델이 ONNX Runtime과 비슷한 성능을 냄
- **주의**: 시작 온도와 열 스로틀링의 영향을 받으므로 성능 보장값이 아님

---

## 실습 7 - 컴파일만으로는 빨라지지 않는다 (Autotuning)

- **스케줄(schedule)**: 연산 커널의 루프를 나누고(타일링), SIMD로 묶고(벡터화), 코어에 나누는(병렬화) 방법의 조합
- **오토튜닝(autotuning)**: 후보 스케줄을 실제 기계에서 실행·측정해 가장 빠른 스케줄을 고르는 과정
  - 저장소의 Pi 4 튜닝 DB는 3093개 후보를 측정해 만든 결과
- **튜닝하지 않은 출력**: ONNX Runtime보다 약 **1000배 느림**
- **오토튜닝의 효과**: 튜닝한 스케줄이 약 **47배**의 성능 향상을 만들어 냄

---

## 실습 7 - 컴파일만으로는 빨라지지 않는다 (Cont'd - 1)

### 스케줄은 측정한 기계에만 최적 (Schedules Belong to the Machine)

| 튜닝한 기계   | 실행한 기계 | 결과     |
| ------------- | ----------- | -------- |
| 10코어 노트북 | Pi 4        | 0.88 fps |
| Pi 4          | Pi 4        | 9.31 fps |

- **원인**: 코어 수, 캐시 크기, SIMD 폭이 다르면 가장 빠른 스케줄도 달라짐
- **저장소의 선택**: Pi 4에서 측정한 튜닝 DB를 커밋해 두었으므로 재측정 불필요
- **재측정 비용**: 다른 보드를 대상으로 하면 `scripts/tune-on-pi.sh`로 수 시간 동안 다시 측정

---

## 실습 7 - 해상도 선택 (Input Size)

- **입력 크기**: YOLOv8 기본값 640×640이 아니라 **320×320**으로 동작
- **연산량**: 픽셀 수가 한 변의 제곱에 비례하므로 한 변을 절반으로 줄이면 약 4분의 1
- **출력 후보 수**: 320 입력에서 40² + 20² + 10² = 2100개(출력 형태 `[1,84,2100]`)
- **선택 이유**: Pi 4에서 실시간으로 쓸 수 있는 속도를 얻기 위함

### 대가 (Trade-offs)

- **정확도**: 작고 먼 물체의 검출 정확도 하락, 가까운 사람은 안정적으로 검출
- **일관성**: 크기를 바꾸려면 같은 크기로 모델을 다시 내보내고 다시 튜닝해야 함

---

## 실습 7 - 빌드 구성 (Who Builds What)

- **역할 분담**: 두 대가 관여하며, **파이에서는 아무것도 컴파일하지 않음**

| 역할   | 하는 일                | 필요 조건                                 |
| ------ | ---------------------- | ----------------------------------------- |
| 호스트 | 모델 변환, 크로스 빌드 | Docker(Buildx), Python 변환 환경, 8GB     |
| 파이   | 실행만                 | 64비트 OS, 시스템 glibc와 ALSA 라이브러리 |

- **자체 포함 아티팩트**: 필요한 라이브러리를 폴더 안에 함께 두고 `$ORIGIN` 런패스로 찾음
  - **런패스(RPATH)**: 실행 파일에 기록된 공유 라이브러리 검색 경로
  - **`$ORIGIN`**: 실행 파일이 있는 디렉터리, 폴더째 옮겨도 `LD_LIBRARY_PATH` 설정 불필요
- **설치 불필요**: 파이에는 Python, Docker, TVM을 설치하지 않음

---

## 실습 7 - 로컬 빌드와 시험 (Build and Test)

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release \
      -DCCTV_MODE=native -DBUILD_TESTS=ON
cmake --build build -j
ctest --test-dir build --output-on-failure

./build/cctv_app --port 8080 --static app/static
```

- **요구 사항**: CMake 4.0 이상, C++14 컴파일러, 의존성(GoogleTest 등)을 받기 위한 네트워크
- **자리표시자(placeholder)**: 모델이 없을 때 대신 링크되어 검출 결과 0개를 반환하는 구현
  - 저장소를 막 복제한 상태에서도 빌드와 시험이 통과
  - 파이프라인 동작만 확인하며 객체 검출은 확인하지 않음
- **장치가 없을 때**: 카메라·마이크를 열 수 없으면 합성 영상(`synthetic`)과 무음(`silent`)으로 대체

---

## 실습 7 - 아티팩트 만들기 (Producing `dist/`)

```bash
# 1. conversion virtualenv (host only, never on the Pi)
python3 -m venv .venv-convert
.venv-convert/bin/pip install -r models/convert/requirements.txt
# 2. export yolov8n.onnx at 320x320
./models/download.sh
# 3. compile with the committed tuning database
.venv-convert/bin/python models/convert/tvm_compile.py \
  --onnx models/onnx/yolov8n.onnx \
  --input-name images --input-shape 1,3,320,320 \
  --out yolov8n_tuned --target arm64 \
  --emit-embed src/backend_native/generated \
  --tune-db models/tuning/rpi4
# 4. cross-build both artifacts into dist/
./scripts/build-pi-artifacts.sh
```

---

## 실습 7 - 아티팩트 만들기 (Cont'd - 1)

- **1단계**: PyTorch와 TVM을 포함하므로 수 GB의 디스크가 필요한 변환 전용 가상 환경
- **2단계**: Ultralytics 가중치를 320×320 입력의 `yolov8n.onnx`로 내보냄
- **3단계**: 튜닝 DB를 적용해 aarch64용 연산 커널(`.o`)과 가중치를 `generated/`에 생성
  - `--input-shape`를 생략하면 기본값 `1,3,640,640`이 적용되어 라이브러리와 맞지 않음
  - `applied tuned schedules: 87 parallel, 158 vectorized loops`처럼 적용 개수를 출력해야 정상
  - 개수가 0에 가까우면 DB가 적용되지 않았음을 뜻하며 `native`가 느려짐
- **4단계**: Docker Buildx로 두 모드를 크로스 빌드해 `dist/pi4-onnx`, `dist/pi4-native`에 저장
  - 실습 1처럼 호스트 OS와 무관하게 같은 빌드 환경에서 aarch64 바이너리 생성

---

## 실습 7 - 파이에서 실행 (Running on the Pi)

```bash
scp -r dist/pi4-* pi@raspberrypi.local:~/
sudo usermod -aG video,audio "$USER"   # log out and back in

cd ~/pi4-native && ./cctv_app --port 8080 --static ./static
# then open http://raspberrypi.local:8080/
```

- **장치 확인**: 시작 배너에 `video source : v4l2:/dev/video0`이 보여야 정상
  - `synthetic` 또는 `silent`이면 장치를 열지 못했음을 뜻함
- **동시 실행 금지**: 두 모드가 같은 카메라와 포트를 사용하므로 하나씩 실행
- **접근 제한**: `--token`을 주면 `/stream`, `/status` 요청에 토큰 쿼리가 필요
  - 서버는 TLS 없는 HTTP이므로 신뢰할 수 있는 로컬 네트워크에서만 사용

---

## 실습 7 - 전력과 발열 (Power and Heat)

- **스로틀링**: 전압 부족이나 과열 시 펌웨어가 CPU 클록을 낮추는 동작, 별도의 오류 메시지 없음
- **발열**: 방열 없이 추론을 계속하면 SoC 온도가 80℃에 도달해 프레임률이 떨어짐

```bash
vcgencmd get_throttled   # 0x0 is healthy
vcgencmd measure_temp
```

- **`get_throttled` 예**: `0x50005`는 저전압과 스로틀링이 현재 발생 중이며 부팅 이후에도 발생했음을 의미

| 증상                         | 원인                        |
| ---------------------------- | --------------------------- |
| `cannot execute binary file` | 32비트 OS — `aarch64` 확인  |
| `video source : synthetic`   | 카메라 미개방, `video` 그룹 |
| 시간이 지나며 프레임률 하락  | 열 스로틀링 — 팬 장착       |

---

## 실습 7 - CI/CD (GitHub Actions)

- **CI(Continuous Integration)**: 커밋마다 빌드와 테스트를 자동으로 실행하는 방식
- **CD(Continuous Delivery)**: 검증된 결과물을 자동으로 배포하는 방식
- **GitHub Actions**: `.github/workflows/*.yml`에 정의한 작업을 GitHub 서버에서 실행하는 서비스

| 워크플로       | 하는 일                                                         |
| -------------- | --------------------------------------------------------------- |
| `ci.yml`       | PR과 `main` 푸시에서 빌드, 새니타이저, 커버리지 등 9개 작업 실행 |
| `learn-ci.yml` | 수동으로만 실행하는 학습용 축약 파이프라인                      |
| `release.yml`  | `main`의 CI 성공 후 x86_64 개발용 자리표시자 라이브러리 배포    |

- **릴리스의 한계**: 릴리스 결과물은 파이용 검출기가 아니며, 파이 아티팩트는 직접 빌드
- **커버리지**: 테스트가 실행한 코드 줄의 비율, Codecov가 집계해 PR과 배지에 표시

---

## 실습 7 - 성능 비교 자동화 (Benchmark)

```bash
python bench/compare.py --real-model   # build each mode, then measure
cat bench/reports/comparison.md
```

- **측정 방법**: 두 모드를 각각 **별도로 빌드한 프로세스**에서 측정
- **측정 항목**: 지연 시간, 최대 상주 메모리(peak RSS), 라이브러리 크기
- **`--real-model` 생략 시**: `native`는 자리표시자를 측정하므로 추론 성능 비교가 아님
- **fps 열 없음**: fps는 `1000 / 지연(ms)`이므로 같은 사실을 두 번 적으면 반올림 차이로 어긋남
- **원칙**: 같은 측정값은 한 가지 형태로만 기록

---

## 실습 7 - 라이선스 경계 (License)

- **카피레프트(copyleft)**: 파생 저작물도 같은 라이선스로 소스를 공개하도록 요구하는 방식
- **AGPL-3.0**: 네트워크 서비스로 제공할 때도 사용자에게 소스 제공 의무를 부과하는 카피레프트 라이선스
- **YOLOv8**: Ultralytics가 AGPL-3.0 또는 별도의 상용 라이선스로 제공
- **허용형(permissive) 라이선스**: 저작권 고지만 유지하면 수정, 배포, 상용 이용을 허용
  - 프로젝트 소스는 Apache-2.0
  - 의존성: ONNX Runtime(MIT), TVM(Apache-2.0), GoogleTest(BSD-3-Clause), cpp-httplib(MIT), stb

---

## 실습 7 - 라이선스 경계 (Cont'd - 1)

### 기억할 경계 (Obligations)

- **의무 발생**: 바이너리로 배포하거나 네트워크 서비스로 운영하면 AGPL 의무가 발생
- **저장소 공개만으로는 부족**: 배포·운영 형태마다 각 구성 요소의 소스 제공 의무를 따로 확인
- **`native` 모드**: 가중치를 기계어 코드로 컴파일해도 AGPL 의무가 사라지지 않음
- **상용 운영**: AGPL 의무를 모두 이행하거나 Ultralytics의 상용 라이선스를 구매

---

## 실습 7 - 과제 (Tasks)

1. 저장소를 막 복제한 상태에서 빌드와 테스트를 통과시키고 자리표시자 동작을 확인
2. 두 모드의 아티팩트를 만들어 **폴더 크기**를 비교
3. 파이에서 두 모드를 차례로 실행해 프레임률과 온도를 기록
4. 팬 유무에 따른 5분간 프레임률 변화를 그래프로 제시
5. `bench/compare.py --real-model`을 실행해 보고서를 첨부

### 고찰 항목

- 모델을 코드로 컴파일했을 때 **성능 외에** 무엇이 좋아지는가
- 오토튜닝 DB가 없으면 왜 느린가, 그리고 왜 기계마다 달라야 하는가
- 이 프로젝트를 상용으로 쓰려면 무엇을 해결해야 하는가

---

## 한 학기 정리 (Course Summary)

| 실습 | 핵심 내용                                            |
| ---- | ---------------------------------------------------- |
| 1    | 호스트에서 타깃 바이너리를 만들고 환경을 고정하는 법 |
| 2    | 디지털 입출력, 디바운스, PWM, 상태 기계              |
| 3    | 비트뱅잉, SPI, 펄스 폭 측정 방식의 차이              |
| 4    | 주기가 다른 일의 분리와 공유 상태 보호               |
| 5    | 장치가 속도를 정하는 입력과 오버런 처리              |
| 6    | 버퍼를 주고받는 스트리밍 I/O와 컨테이너 기록         |
| 7    | 모델 관리, 배포 자동화, 라이선스 경계                |
