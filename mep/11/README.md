<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 2 - LED와 스위치, PWM, 상태 기계

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 2 - 목표 (Goals)

- 디지털 **출력**을 통한 LED 구동 및 디지털 **입력**을 통한 스위치 상태 감지
- 기계식 접점 연결 시 발생하는 **스위치 바운싱**의 소프트웨어 디바운스 필터링
- **소프트웨어 PWM**을 활용한 디지털 핀 기반의 LED 디밍 제어
- 시간 지연과 외부 이벤트가 복합된 시스템을 **유한 상태 기계(FSM)로 모델링**

| 파일명 | 주제 |
| :--- | :--- |
| `00_led_button.cc` | 디지털 입출력 제어 및 디바운스 알고리즘 |
| `01_pwm_dimmer.cc` | 소프트웨어 PWM 기반 LED 밝기 제어 |
| `02_state_machine.cc` | 시간·이벤트 기반 FSM 상태 전이 제어 |

---

## 실습 2 - 사용 부품과 핀 배치 (Parts and Pins)

| 부품명 | 수량 | 회로 결선 규격 |
| :--- | :---: | :--- |
| **LED** | 2개 | 330Ω 전류 제한 저항 직렬 연결 |
| **푸시버튼** | 2개 | 10kΩ 외장 풀업 저항 구성 |
| **점퍼 케이블** | 다수 | 브레드보드 신호 배선 |

| 신호 명칭 | BCM | 담당 프로그램 |
| :--- | :---: | :--- |
| **LED(빨강)** | 17 | 2-A, 2-B, 2-C |
| **LED(초록)** | 27 | 2-C |
| **버튼 1** | 23 | 2-A, 2-C |
| **버튼 2** | 24 | 2-B |

---

## 실습 2 - 풀업 회로의 동작 (Pull-Up)

![h:220 center](img/05-switch.png)

- **택트 스위치 내부 구조**: 마주 보는 두 쌍의 핀이 내부에서 상시 연결된 구조
- **외장 풀업 저항 구성**: 입력 핀을 10kΩ 저항을 통해 3.3V에 연결, 스위치는 핀과 GND 사이 결선
  - 저항 없이 전원과 접지에 직결 시 스위치 입력 순간 **단락(Short)** 발생
- **동작 논리 레벨**: 액티브 LOW 방식(평상시 **HIGH**, 버튼 누름 시 **LOW**)

---

## 실습 2-A - 회로도 (Schematic)

![h:330 center](img/04-lab01-circuit.png)

---

## 실습 2-A - 브레드보드 배치 (Breadboard Layout)

![h:340 center](img/20-lab01-layout.png)

---

## 실습 2 - 구성과 빌드 (Layout and Build)

```text
mep/
├── common/
│   ├── gpio.hpp
│   └── signal_stop.hpp
└── lab02/src/
    ├── 00_led_button.cc
    ├── 01_pwm_dimmer.cc
    └── 02_state_machine.cc
```

```bash
cd mep/lab02/src

# Compile and link the target binary with libgpiod
clang++ -std=c++14 -Wall -Wextra -I../../common 00_led_button.cc -o led -lgpiod
./led
```

- 세 실습 프로그램 모두 공용 헤더(`-I../../common`)를 참조하여 동일하게 빌드

---

## 실습 2-A - 핀과 상수 (Pins and Constants)

[//]: # "INCLUDE: ./mep/11/src/00_led_button.cc --from 10 --to 15 --no-comment"

- **BCM 번호 지정**: 헤더 커넥터의 물리 핀 번호가 아닌 Broadcom SoC 기준 BCM 라인 번호 사용

---

## 실습 2-A - 라인 확보 (Claiming the Lines)

[//]: # "INCLUDE: ./mep/11/src/00_led_button.cc --from 27 --to 32 --no-comment"

- **자원 할당 및 검증**: 생성자에서 라인 오프셋을 요청하며, `ok()`를 통해 초기화 성공 검증
- **RAII 자동 반환**: 객체 수명 종료 시 소멸자가 커널 자원을 안전하게 자동 해제

---

## 실습 2-A - 디바운스 규칙 (Debounce Rule)

[//]: # "INCLUDE: ./mep/11/src/00_led_button.cc --from 44 --to 57 --no-comment"

---

## 실습 2 - 스위치 바운싱 (Switch Bouncing)

![h:180 center](img/09-chattering.png)

- **채터링(Chattering)**: 기계식 접점이 맞닿는 순간 수 ms 동안 미세 진동으로 신호 반복 진동
- **즉시 감지 원칙**: 최초 눌림 신호는 지연 없이 즉시 수신하여 응답성 확보
- **안정 상태 복귀**: 입력 핀이 지정 시간 동안 지속적으로 HIGH를 유지해야 무장(`armed`) 상태로 복귀
- **단순 딜레이의 한계**: 고정 시간 지연 방식은 노이즈 지속 시 중복 입력 오인식 유발

---

## 실습 2-B - 디지털 핀으로 밝기 만들기 (PWM)

![h:190 center](img/06-pwm.png)

- **펄스 폭 변조(PWM)**: 고속 스위칭과 듀티비 조절을 통해 등가 아날로그 전압 모사
- **듀티비(Duty Cycle)**: 한 주기 내에서 HIGH 상태가 유지되는 시간의 백분율 비율로 밝기 결정
- **주파수 특성**: 100단계 × 100µs = 10ms 주기(100Hz 기준), OS 스케줄링 오버헤드로 실측치는 변동

---

## 실습 2-B - PWM 상수 (PWM Constants)

[//]: # "INCLUDE: ./mep/11/src/01_pwm_dimmer.cc --from 13 --to 18 --no-comment"

---

## 실습 2-B - 순수 함수 (Pure Functions)

[//]: # "INCLUDE: ./mep/11/src/01_pwm_dimmer.cc --from 24 --to 31 --no-comment"

- **하드웨어 독립성**: I/O 접근이 없는 순수 함수로 구성되어 호스트 PC 환경에서 단위 테스트 가능

---

## 실습 2-B - PWM 주기 (One PWM Period)

[//]: # "INCLUDE: ./mep/11/src/01_pwm_dimmer.cc --from 51 --to 70 --no-comment"

- **인터리빙 처리**: PWM 듀티 루프 내부에서 버튼 입력을 검사하여 밝기 출력과 입력 감지 병행

---

## 실습 2-B - 소프트웨어 PWM과 하드웨어 PWM

| 구분 | 소프트웨어 PWM | 하드웨어 PWM |
| :--- | :--- | :--- |
| **신호 생성** | CPU 코어가 직접 토글 | SoC 전용 타이머 회로 |
| **핀 제약** | 모든 범용 GPIO 지원 | 전용 PWM 지정 핀 한정 |
| **CPU 부하** | 주기적 스케줄링 부담 | 레지스터 설정 후 부하 없음 |
| **신호 지터** | OS 스케줄링 지연 발생 | 하드웨어 클록 기반(지터 없음) |

- **용도 구분**: 단순 LED 디밍은 소프트웨어 PWM으로 충분하나, 서보·모터 정밀 제어는 하드웨어 PWM 필수

---

## 실습 2-C - 왜 상태 기계인가 (Why a State Machine)

- 시간 경과와 비동기 이벤트가 결합될 때 단순 플래그 제어는 코드 복잡도 급증 초래
- **상태 정의 다이어그램**: 시스템 상태와 전이 규칙을 분리하여 직관적인 동작 파악 가능

| 구성 요소 | 실습 적용 내용 |
| :--- | :--- |
| **상태(State)** | `CAR GO`, `WARN`, `WALK` 3단계 정의 |
| **시간 전이** | 설정 타임아웃 경과 시 자동 다음 상태 전이 |
| **이벤트 전이** | 보행자 버튼 입력 시 차량 주행(`CAR GO`) 구간 단축 |
| **출력(Output)** | 현재 활성 상태에 종속되는 무어(Moore) 머신 방식 LED 점등 |

---

## 실습 2-C - 상태 전이 (State Transition)

| 상태 | 지속 시간 | 적색 LED | 녹색 LED | 다음 상태 |
| :--- | :---: | :---: | :---: | :--- |
| `CAR GO` | 10초 | Off | On | `WARN` |
| `WARN` | 3초 | Off | 점멸 | `WALK` |
| `WALK` | 8초 | On | Off | `CAR GO` |

![h:260 center](img/22-crosswalk_state_diagram_final.png)

- **보행자 버튼**: `CAR GO` 잔여 시간을 최대 2초로 단축(2초 이하 잔여 시 현행 유지)
- **입력 큐잉**: `WALK` 중 입력은 다음 주기에 반영, `WARN` 중 입력은 기처리 간주
- **멱등성 보장**: 버튼 중복 입력 시 시간 연장 없이 1회 단축 요청으로 한정

---

## 실습 2-C - 회로도 (Schematic)

![h:330 center](img/08-lab02-circuit.png)

---

## 실습 2-C - 브레드보드 배치 (Breadboard Layout)

![h:340 center](img/21-lab02-layout.png)

---

## 실습 2-C - 상태 정의 (Defining the States)

[//]: # "INCLUDE: ./mep/11/src/02_state_machine.cc --from 20 --to 27 --no-comment"

---

## 실습 2-C - 출력 함수 (Output Functions)

[//]: # "INCLUDE: ./mep/11/src/02_state_machine.cc --from 32 --to 37 --no-comment"

---

## 실습 2-C - 전이 규칙 (Transitions)

[//]: # "INCLUDE: ./mep/11/src/02_state_machine.cc --from 74 --to 84 --no-comment"

- **우선순위 제어**: 비동기 이벤트 전이를 선행 평가한 후 타이머 기반 시간 전이 처리
- **순서 역전 주의**: 평가 순서가 바뀔 경우 보행자 요청이 한 주기 지연되어 반영됨

---

## 실습 2 - 과제 (Tasks)

1. **실습 2-A 검증**: 버튼 토글 동작 확인 및 디바운스 시간을 0으로 수정하여 채터링 현상 관찰
2. **실습 2-B 검증**: `kPwmSteps`를 10으로 축소하여 플리커링(깜빡임) 인지 임계점 탐색
3. **실습 2-C 확장**: 황색 LED를 추가하여 `WARN` 구간을 독립 LED로 시각화
4. **실습 2-C 로깅**: `WALK` 구간 내 버튼 입력 시 보행자 요청 플래그의 보류 및 전이 로그 확인

### 고찰 항목

- **디바운스 알고리즘 한계**: 단순 고정 시간 지연 방식이 오동작하는 구체적 시나리오 분석
- **감성 조명 PWM 설계**: 자연스러운 촛불 깜빡임 구현을 위한 듀티비(Duty Cycle) 변조 및 갱신 주기 설계 방안
