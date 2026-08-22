<!-- _class: lead -->
# 마이크로임베디드프로그래밍

## 임베디드 시스템 개론

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 임베디드 시스템의 정의 (Definition)

![h:400 center](img/00-embedded-system.png)

- 가전제품이나 기계 장치 내부에 탑재되어 **특정한 하나의 목적(단일 기능)만을 수행하는 아주 작은 컴퓨터 시스템**
  - 범용 컴퓨터(PC, 서버)와 달리 용도가 고정되어 있음

---

## 임베디드 시스템의 정의 (Definition) (Cont'd)

### 범용 시스템과의 비교

| 항목 | 범용 시스템 | 임베디드 시스템 |
| --- | --- | --- |
| 용도 | 다목적 | 특정 목적 |
| 자원 | 풍부 | 제한적(CPU, 메모리, 전력) |
| 사용자 인터페이스 | 화면·키보드 | 없음·최소 |
| 실시간성 | 대체로 불필요 | 요구되는 경우가 많음 |
| 전원 | 상시 공급 | 배터리 구동이 흔함 |

---

## 임베디드 시스템의 제약 (Constraints)

- **자원 제약**: CPU 성능, 메모리 용량, 저장 공간이 모두 제한됨
- **전력 제약**: 배터리로 구동되는 경우 소비 전력이 곧 사용 시간
- **실시간 제약**: 정해진 시간 안에 반드시 응답해야 하는 경우가 존재
  - 경성 실시간(hard real-time): 마감 시간을 넘기면 시스템 실패
  - 연성 실시간(soft real-time): 품질이 저하되지만 동작은 유지
- **환경 제약**: 온도, 진동, 습도 등 가혹한 조건에서 동작

### 제약이 프로그래밍에 미치는 영향

- 동적 할당을 최소화하고, 실행 시간을 예측 가능하게 유지
- 부동소수점 대신 고정소수점을 쓰는 경우가 있음
- 코드 크기와 실행 속도의 균형을 항상 고려

---

## 임베디드 시스템의 구성 (Components)

![h:300 center](img/01-system-block.png)

- **프로세서**: MCU(마이크로컨트롤러) 또는 MPU(마이크로프로세서)
- **메모리**: 코드 저장용 플래시, 실행용 RAM
- **보조 회로 및 IC**: PMIC(전원 관리), RTC, 클럭/리셋 등 시스템 안정 동작 지원
- **주변장치**: GPIO, UART, I2C, SPI, ADC, PWM, 타이머
- **센서와 액추에이터**: 외부 세계와의 접점
- **소프트웨어**: 베어메탈 펌웨어 또는 운영체제 기반 응용

---

## MCU와 MPU (Microcontroller vs Microprocessor)

![h:195 center](img/02-mcu-vs-mpu.png)

| 항목 | MCU | MPU |
| --- | --- | --- |
| 대표 예 | STM32, ESP32, RP2350 | Raspberry Pi, NXP i.MX, Rockchip RK3588 |
| 메모리 | 칩 내부에 통합 | 외부 DRAM 필요 |
| 저장장치 | 내장 플래시 | SD 카드, eMMC |
| 운영체제 | 없음·RTOS | Linux 등 범용 OS |
| 부팅 시간 | 수 밀리초 | 수 초 |

> MCU는 "칩 하나로 완결", MPU는 "주변 부품이 필요한 작은 컴퓨터"

---

## 임베디드 시스템의 응용 (Applications)

![h:200 center](img/03-applications.png)

- **가전**: 세탁기, 냉장고, 로봇청소기
- **자동차**: ECU, ADAS, 인포테인먼트
- **의료기기**: 혈당측정기, 인퓨전 펌프
- **산업**: PLC, 공장 자동화, 로보틱스
- **IoT**: 스마트 홈, 환경 센서 네트워크
- **국방·항공**: 비행 제어, 항법 장치

### 최근 경향

- 단순 제어에서 **엣지 AI**(장치에서 직접 추론)로 확장
- 네트워크 연결이 기본이 되면서 **보안**이 핵심 요구사항으로 부상
- 소프트웨어 규모가 커지며 **빌드·배포 엔지니어링**의 중요성 증가

---

## 소프트웨어 실행 환경의 세 계층 (Three Layers)

![h:300 center](img/04-three-layers.png)

- 위로 갈수록 **개발이 편해지고**, 아래로 갈수록 **예측 가능성과 효율이 높아짐**
- 어느 계층을 고르느냐가 곧 **플랫폼 선택**으로 이어짐

---

## 베어메탈 (BM, Bare Metal)

![h:450 center](img/05-bm.png)

- **운영체제 없이 응용 코드가 하드웨어를 직접 제어**하는 방식
- 부팅 후 코드가 CPU를 독점
  - 프로그램이 곧 시스템을 의미

---

## 베어메탈 (BM, Bare Metal) (Cont'd - 1)

```c
int main()
{
    hardware_init();          /* clocks, GPIO, timers */
    while (1) {               /* super loop */
        read_sensors();
        update_control();
        drive_outputs();
    }
}
```

- 시간에 민감한 처리는 **인터럽트 서비스 루틴**(ISR)에서 수행
- 메인 루프와 ISR이 공유하는 변수에는 `volatile`이 필요 — 6장에서 상세히 다룸

---

## 베어메탈 (BM, Bare Metal) (Cont'd - 2)

### 베어메탈의 장단점 (Trade-offs)

| 장점 | 단점 |
| --- | --- |
| 완전히 예측 가능한 동작 | 기능이 늘면 복잡도가 급증 |
| 부팅이 매우 빠름 | 멀티태스킹을 직접 구현해야 함 |
| 아주 작은 메모리로도 동작 | 네트워크·파일시스템을 직접 구현 |
| 소비 전력을 최소화하기 쉬움 | 이식성이 낮음 |
| OS 라이선스·오버헤드 없음 | 디버깅 도구가 제한적 |

#### 언제 쓰는가

- 기능이 단순하고 명확할 때(모터 제어, 센서 노드)
- **경성 실시간**이 요구될 때 — OS 스케줄러의 지연을 허용할 수 없는 경우
- 원가와 전력을 극한으로 줄여야 할 때

---

## RTOS (Real-Time Operating System)

![h:450 center](img/06-rtos.png)

- 베어메탈과 범용 OS의 **중간 계층**
- 여러 작업을 **태스크**로 나누고, 스케줄러가 우선순위에 따라 전환

---

## RTOS (Real-Time Operating System) (Cont'd - 1)

```c
#include "projdefs.h"  /* Project Definitions, for pdMS_TO_TICKS */

/* Concept: two tasks run independently at different periods. */
void SensorTask(void* arg) {
  for (;;) {
    ReadSensor();
    vTaskDelay(pdMS_TO_TICKS(100));  /* every 100 ms */
  }
}

void NetworkTask(void* arg) {
  for (;;) {
    SendPacket();
    vTaskDelay(pdMS_TO_TICKS(1000));  /* every 1 s */
  }
}
```

- 커널 API(e.g., `xTaskCreate`)로 등록된 함수는 커널의 관리를 받아 독립된 실행 흐름으로 동작
- **우선순위 기반 선점형 스케줄링** — 높은 우선순위 태스크가 즉시 CPU를 가져감
- 태스크 간 통신 수단 제공: 큐, 세마포어, 뮤텍스
- 커널이 작아 MCU에 탑재 가능

---

## RTOS (Real-Time Operating System) (Cont'd - 2)

### RTOS Task Scheduling

![center](img/07-rtos-task-scheduling.png)

---

## 범용 OS (General-Purpose OS)

- Linux 등 **완전한 운영체제**를 탑재하는 방식
- 프로세스, 가상 메모리, 파일시스템, 네트워크 스택을 모두 제공
- 방대한 기존 소프트웨어 자산을 그대로 사용(웹 서버, 데이터베이스, 각종 라이브러리)
- 표준 개발 도구와 디버거를 사용 — 개발 생산성이 높음
- MMU(Memory Management Unit)가 필요하므로 MPU급 하드웨어가 요구됨
- 부팅에 수 초가 걸리고, 응답 지연이 결정적으로 보장되지 않음

> 카메라·네트워크·웹 서비스를 다루려면 범용 OS가 사실상 필수

---

## 세 계층 비교 (Comparison)

| 항목 | 베어메탈 | RTOS | 범용 OS |
| --- | --- | --- | --- |
| 필요 메모리 | 매우 작음 | 작음 | 큼 |
| 부팅 시간 | 수 밀리초 | 수십 밀리초 | 수 초 |
| 실시간성 | 최고 | 높음(결정적) | 낮음(비결정적) |
| 멀티태스킹 | 직접 구현 | 커널이 제공 | 커널이 제공 |
| 네트워크·파일시스템 | 직접 구현 | 라이브러리 추가 | 기본 제공 |
| 개발 난이도 | 높음 | 중간 | 낮음 |
| 대표 하드웨어 | RP2350, STM32 | ESP32, STM32 | Raspberry Pi, Jetson |

---

## 저전력 플랫폼 (Low-Power Platforms)

- 배터리로 수개월~수년 동작해야 하는 장치의 설계 기준
- 핵심은 **평균 소비 전류** — 대부분의 시간을 잠들어 있게 만드는 것

### 전력 모드

| 모드 | 상태 | 상대적 소비 |
| --- | --- | --- |
| 동작(active) | CPU 실행 중 | 가장 큼 |
| 슬립(sleep) | CPU 정지, 주변장치 동작 | 중간 |
| 딥슬립(deep sleep) | 대부분 차단, 타이머·외부 인터럽트로 기상 | 매우 작음 |

$$\text{Battery life (h)} \approx \frac{\text{Battery capacity (mAh)}}{\text{Average current (mA)}}$$

---

## 저전력 플랫폼 (Low-Power Platforms) (Cont'd)

### Current Consumption vs Time

![center](img/08-power-profile.png)

---

## 저전력 설계의 원칙 (Low-Power Design)

- **가능한 한 빨리 처리하고 즉시 잠든다** — "race to sleep"
  - SIMD 등의 연산 최적화는 전력 절감으로 이어짐 — 5장에서 상세히 다룸
- 폴링 대신 **인터럽트**로 기상 — 대기 중 CPU를 사용하지 않음
- 무선 송신은 소모가 가장 큼 — **전송 빈도와 페이로드를 줄이는 것**이 최우선
- 사용하지 않는 주변장치의 클록을 차단

### 범용 OS와 저전력의 관계

- Linux 급 시스템은 상시 동작하는 프로세스가 많아 딥슬립이 어려움
- 배터리 장치라면 **MCU + 베어메탈/RTOS** 조합이 일반적

---

## 플랫폼 지도 (Platform Map)

| 계층 | 대표 플랫폼 | 실행 환경 |
| --- | --- | --- |
| 교육용 MCU | Raspberry Pi Pico(RP2350) | 베어메탈 / RTOS |
| 범용 MCU | STMicroelectronics STM32 | 베어메탈 / RTOS |
| 무선 MCU | Espressif ESP32 | RTOS |
| 산업용 MPU | NXP i.MX | Linux |
| 고성능 SBC SoC | Rockchip RK3588 | Linux / Android |
| 엣지 AI 모듈 | NVIDIA Jetson | Linux |
| 고성능 AP | Qualcomm Snapdragon | Linux / Android |
| 교육·프로토타이핑 | Raspberry Pi | Linux |

---

## STMicroelectronics STM32

![h:250 center](img/09-stm32.png)

- ARM **Cortex-M** 계열 MCU 제품군 — 임베디드 산업 현장의 사실상 표준

| 항목 | 내용 |
| --- | --- |
| 구성 | Cortex-M0+ ~ M33 + 주변장치 내장 |
| 실행 환경 | 베어메탈, FreeRTOS, Zephyr |
| 강점 | 핀 호환을 유지하며 성능·메모리를 바꿔 갈 수 있는 넓은 제품군 |
| 주 용도 | 산업 제어, 모터 제어, 가전, 의료기기 |

- CubeMX로 초기화 코드를 생성해 주변장치 설정 부담이 작음

---

## Espressif ESP32

![h:250 center](img/10-esp32.png)

- **WiFi와 Bluetooth를 칩에 내장**한 MCU — IoT 분야에서 가장 널리 쓰임

| 항목 | 내용 |
| --- | --- |
| 구성 | Xtensa 또는 RISC-V + WiFi·BLE |
| 실행 환경 | FreeRTOS 기본 내장(ESP-IDF) |
| 강점 | 무선 모듈이 없어 원가·기판 면적 절감, 딥슬립 지원 |
| 주 용도 | 스마트홈, 무선 센서 노드, 시제품 |

- 배터리 센서 노드로도 쓰이나, 송신 구간의 전류 소모가 큼

---

## Raspberry Pi Pico (RP2350)

![h:250 center](img/11-pico.png)

- **라즈베리파이 재단(Raspberry Pi Foundation)이 만든 MCU 보드** — Linux는 동작하지 않음

| 항목 | 내용 |
| --- | --- |
| 구성 | Cortex-M33 또는 RISC-V(Hazard3) + PIO |
| 실행 환경 | 베어메탈(C/C++ SDK), FreeRTOS, MicroPython |
| 강점 | PIO로 까다로운 타이밍 신호를 CPU 부담 없이 생성 |
| 주 용도 | 교육, 센서 제어, 실시간 신호 생성 |

- 부팅 시 Arm과 RISC-V 중 하나를 고르는 흔치 않은 구조

---

## NVIDIA Jetson

![h:250 center](img/12-nvidia-jetson.png)

- GPU를 탑재한 **엣지 AI 전용 모듈** — 장치에서 직접 딥러닝 추론을 수행

| 항목 | 내용 |
| --- | --- |
| 구성 | Cortex-A + CUDA GPU + 딥러닝 가속기(DLA) |
| 실행 환경 | Linux(JetPack) |
| 강점 | 데스크톱과 같은 CUDA 생태계로 학습 모델을 그대로 이식 |
| 주 용도 | 로보틱스, 자율주행, 드론 |

- 제품군은 Orin Nano부터 AGX Orin까지 성능 단계별로 구성

---

## Qualcomm

![h:250 center](img/13-qualcomm.png)

- 모바일 AP 기술을 임베디드로 확장한 **고성능 응용 프로세서**

| 항목 | 내용 |
| --- | --- |
| 구성 | Cortex-A + GPU + DSP + NPU |
| 실행 환경 | Linux, Android |
| 강점 | 작업별로 효율적인 유닛에 배분, 카메라·통신 처리에 강함 |
| 주 용도 | 스마트폰, 로보틱스, XR, 차량 |

- 대표 제품군은 Snapdragon과 그 IoT·로보틱스 파생 계열

---

## 특화 SoC 사례: Ambarella

![h:250 center](img/14-ambarella.png)

- 범용 플랫폼이 아닌, 특정 분야에 극단적으로 특화된 칩의 사례

| 항목 | 내용 |
| --- | --- |
| 구성 | Cortex-A + 영상 인코더 + 전용 AI 엔진 |
| 실행 환경 | Linux |
| 강점 | 고효율 영상 인코딩과 저전력 AI 추론을 동시 수행 |
| 주 용도 | IP 감시 카메라, 차량용 블랙박스, 드론, ADAS |

- 상용 CCTV는 범용 프로세서 대신 영상 처리에 특화된 SoC를 주로 채택

---

## 임베디드 Linux SoC (NXP i.MX / Rockchip RK3588)

![h:250 center](img/15-linux-soc.png)

- 두 계열 모두 라즈베리파이와 같은 **Linux + GPIO** 구조

| 항목 | NXP i.MX | Rockchip RK3588 |
| --- | --- | --- |
| 구성 | Cortex-A53·A55 + NPU | Cortex-A76·A55 + NPU |
| 실행 환경 | Linux | Linux, Android |
| 강점 | 장기 공급 보증, CAN-FD·TSN | 8K 디코딩, 다중 카메라 |
| 주 용도 | 산업 제어, 의료, 차량 | 고성능 SBC, 엣지 AI |

- 산업용은 성능보다 몇 년간 같은 칩을 구매할 수 있는지가 중요

---

## Raspberry Pi

![h:250 center](img/16-rpi.png)

- 교육과 프로토타이핑을 위한 **단일 보드 컴퓨터** — 본 수업의 플랫폼

| 항목 | 내용 |
| --- | --- |
| 구성 | Cortex-A72(arm64) + VideoCore GPU |
| 실행 환경 | Raspberry Pi OS(Linux) |
| 강점 | GPIO와 Linux를 동시에 제공, 방대한 자료와 낮은 가격 |
| 주 용도 | 교육, 개념 검증, 시제품(양산에는 부적합) |

- MPU의 특성(Linux·네트워크)과 MCU의 특성(GPIO 제어)을 함께 경험

---

## 플랫폼 선택 기준 (How to Choose)

1. **경성 실시간이 필요한가** → MCU + 베어메탈/RTOS
2. **배터리로 동작하는가** → 저전력 MCU(STM32 L·U 시리즈 등)
3. **네트워크·파일시스템·웹이 필요한가** → 범용 OS 급 MPU
4. **영상 처리나 AI 추론이 핵심인가** → 전용 SoC·모듈(Ambarella, Jetson, Qualcomm)
5. **양산 규모와 원가는** → 대량 양산일수록 전용 SoC가 유리

> **요구사항이 플랫폼을 결정**

---

## 이 수업이 다루는 범위 (Scope)

- 이 수업은 임베디드 시스템의 두 축을 모두 다룸

### 축 1: 하드웨어 제어

- GPIO를 통한 디지털 입출력
- 센서 프로토콜(온습도, 조도, 초음파)
- 카메라와 마이크 등 멀티미디어 장치

### 축 2: 소프트웨어 엔지니어링

- CMake 기반 빌드 시스템, 크로스 컴파일
- 라이브러리 설계와 최적화
- CI/CD, 라이선스, 배포 파이프라인

> 센서를 동작시키는 것에서 끝나지 않고, **배포 가능한 제품**을 만드는 과정까지 학습함
