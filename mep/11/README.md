<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 센서 통합과 웹 서비스

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 이 장의 구성 (Contents)

| 구분   | 내용                                          |
| ------ | --------------------------------------------- |
| 설계   | 여러 센서를 하나의 프로그램으로 통합하는 구조 |
| 동시성 | 수집 스레드와 서비스 스레드의 분리            |
| 서비스 | HTTP로 측정값을 제공하고 브라우저에서 확인    |

- 지금까지의 실습을 **하나의 시스템으로 합치는** 첫 단계

---

## 왜 통합이 어려운가 (Why Integration Is Hard)

- 센서 하나를 읽는 것과, 여러 센서를 동시에 운용하는 것은 다른 문제

| 문제             | 설명                                             |
| ---------------- | ------------------------------------------------ |
| 주기가 다름      | DHT11은 1초 이상, 초음파는 훨씬 빠르게 측정 가능 |
| 소요 시간이 다름 | 어떤 센서는 읽는 데 수십 ms가 걸림               |
| 실패가 전파됨    | 센서 하나가 멈추면 전체가 멈출 수 있음           |
| 소비자가 다름    | 웹 요청은 언제 올지 모름                         |

### 잘못된 설계

```cpp
while (true) {
  ReadDht11();      /* takes 20 ms or more */
  ReadCds();
  ReadUltrasonic();
  HandleHttpRequest();   /* delayed by the sensor reads above */
}
```

> 하나의 루프에 모두 넣으면 **가장 느린 센서가 전체 응답 속도를 결정**함

---

## 실습 06 - 센서 데이터 실시간 웹서버

<!-- IMAGE [목업] 웹 대시보드 화면 목업 - 온습도·조도·거리 실시간 표시 (img/17-dashboard-mockup.png) -->

- 지금까지의 센서(온습도, 조도, 초음파)를 **하나의 프로그램으로 통합**
- 측정값을 웹 대시보드로 실시간 표현
- 센서 추상화와 모듈 분리를 경험

### 시스템 구성

```text
[DHT11]  ---+
[CdS+ADC]---+--> collector thread --> shared state --> HTTP server --> browser
[HC-SR04]---+                          (mutex)
```

- 센서 수집과 웹 서비스는 **주기가 다르므로** 분리해야 함

---

## 실습 06 - 설계 (Design)

<!-- IMAGE [블록도] 센서 수집 스레드 - 공유 상태 - HTTP 서버 - 브라우저 구성도 (img/16-lab06-architecture.png) -->

### 센서 인터페이스 추상화

```cpp
class Sensor {
 public:
  virtual ~Sensor() = default;
  virtual bool Read(float* out) = 0;
  virtual const char* name() const = 0;
};
```

- 각 센서가 이 인터페이스를 구현하면, 수집 루프는 센서 종류를 몰라도 됨
- 센서를 추가할 때 수집 루프를 수정할 필요가 없음

### 공유 상태

- 수집 스레드가 쓰고 웹 스레드가 읽으므로 **`std::atomic`** 또는 뮤텍스 필요
- `volatile`은 이 목적에 **적합하지 않음**(이론 10주차 참조)

---

## 실습 06 - 구성과 빌드 (Layout and Build)

- 실습 03~05의 센서 코드를 **공용 드라이버 헤더**로 옮기고, 하나의 프로그램이 모두 사용
- 공용 헤더(`common/`)의 **전체 코드는 9장 부록**을 참조 — 필요한 부분은 이 장에서 발췌해 인용

```text
project/
├── common/
│   ├── gpio_helper.hpp        # RAII wrapper
│   ├── signal_stop.hpp        # Ctrl-C stop flag
│   ├── dht11.hpp              # lab 03: single-wire protocol
│   ├── mcp3008.hpp            # lab 04: SPI ADC
│   └── hcsr04.hpp             # lab 05: ultrasonic distance
└── 11/src/
    └── 00_sensor_hub.cc
```

```bash
cd project/11/src
clang++ -std=c++14 -Wall -Wextra -I../../common \
  00_sensor_hub.cc -o sensorhub -lgpiod -llgpio -pthread
./sensorhub                    # Ctrl-C to stop
# then open http://<pi-address>:8080/ in a browser
```

- 스레드를 쓰므로 `-pthread`가 추가로 필요
- 센서 배선은 실습 03~05를 **그대로 합친 것** — 새로 옮길 배선이 없음

---

## 실습 06 - 센서 인터페이스 (Sensor Interface)

- 수집 루프가 센서의 종류를 모르게 하는 것이 목적

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 42 --to 54"

- `Describe()`는 선택 사항 — 채널이 자기 상태를 **이름**으로 설명할 수 있게 함
- DHT11은 한 번의 변환으로 **두 값**을 주므로, 장치 하나를 두 채널이 공유
  - `Dht11Device`가 최소 측정 간격과 캐시를 담당하고, 채널은 그 위의 얇은 껍데기

---

## 실습 06 - 채널 구현 (Channel Implementations)

- DHT11 채널 — `Dht11Humidity`도 습도를 꺼낸다는 점만 다른 같은 모양

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 57 --to 70"

---

## 실습 06 - 채널 구현 (Cont'd - 1)

- 조도 — ADC의 원시 값을 전압으로 바꿔 내보냄

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 88 --to 98"

---

## 실습 06 - 채널 구현 (Cont'd - 2)

- 조도 — 전압만으로는 밝기를 알 수 없으므로 **상태 이름**을 함께 제공

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 99 --to 110"

- 대시보드 표기는 `bright (2.41 V)` 형식 — 상태가 앞, 근거가 되는 전압은 괄호에

---

## 실습 06 - 채널 구현 (Cont'd - 3)

- 거리 — 각 채널은 자기 장치만 알고, 서로를 모름

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 113 --to 124"

---

## 실습 06 - 실패 사유 전달 (Reporting Why)

- 대시보드에 `--`만 뜨면 **어느 배선이 잘못됐는지** 알 수 없음

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 125 --to 140"

---

## 실습 06 - 공유 상태 (Shared State)

- 수집 스레드가 쓰고 웹 스레드가 읽으므로 **뮤텍스**로 보호

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 143 --to 155"

---

## 실습 06 - 스냅샷 (Snapshot)

- 웹 스레드는 **한 회차 전체**를 한 번에 복사해 간 뒤 잠금을 놓음

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 156 --to 173"

---

## 실습 06 - 왜 `atomic`이 아닌가 (Why a Mutex)

- 값이 **여러 개**이므로 각각을 `std::atomic`으로 두는 것만으로는 부족함

```text
collector: writes temp=26 ... (preempted here) ... writes distance=15
web:                snapshot -> temp 26 (this sweep) + distance 8 (last sweep)
```

- 필드마다 원자적이어도 **함께 바뀌지는 않음** → 서로 다른 회차의 값이 섞임
- 한 번에 한 회차만 보이게 하려면 묶어서 잠가야 함
- `volatile`은 이 목적에 **전혀 맞지 않음** — 최적화만 막을 뿐 동기화가 아님

---

## 실습 06 - 실패 격리 (Isolating Failures)

- 센서 하나가 빠져도 나머지는 계속 살아 있어야 함

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 182 --to 194"

- 각 채널의 성공 여부를 함께 저장해 두고, 대시보드는 실패한 값을 `--`로 표시
- DHT11을 뽑아도 조도와 거리는 계속 갱신되는지 확인해 볼 것

---

## 실습 06 - 두 개의 루프 (Two Loops)

- 수집은 0.5초 주기, 웹 응답은 브라우저가 물을 때 — **주기가 다르므로 스레드도 다름**

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 345 --to 355"

---

## 실습 06 - 수락 루프와 종료 (Accept and Shutdown)

[//]: # "INCLUDE: ./mep/11/src/00_sensor_hub.cc --from 361 --to 376"

- `poll()`에 시간 제한을 두어 접속이 없어도 주기적으로 종료 플래그를 확인
- `join()`으로 수집 스레드가 끝나기를 기다린 뒤에야 소켓을 닫음

---

## 실습 06 - 과제 (Tasks)

1. 세 센서를 연결해 대시보드에 네 채널이 모두 갱신되는지 확인
2. DHT11의 데이터선을 뽑고, 나머지 두 센서가 계속 갱신되는지 확인
3. `curl http://localhost:8080/api`로 JSON을 직접 확인
4. 수집 주기를 0.1초로 줄여 보고, DHT11의 `updates` 증가 속도가 왜 그대로인지 설명
5. 센서를 하나 더 추가 — 수집 루프를 고치지 않고도 되는지 확인

### 고찰 항목

- 센서마다 측정 주기가 다를 때(DHT11은 1초 이상) 어떻게 설계했는가
- 수집 스레드와 웹 스레드가 같은 데이터를 접근할 때의 동기화 방법
- 센서 하나가 실패해도 전체가 멈추지 않도록 하려면

---

## 동시성 설계 (Concurrency Design)

<!-- IMAGE [블록도] 센서별 수집 스레드 -> 공유 상태(atomic) -> HTTP 서버 스레드 (img/17-concurrency.png) -->

```text
[collector thread]  --updates periodically-->  [shared state]  <--reads--  [HTTP thread]
                                                    mutex
```

- 수집과 서비스를 **분리**하면 서로의 지연에 영향받지 않음
- 공유 상태 접근에는 6장에서 배운 **`std::atomic`** 또는 뮤텍스를 사용
  - `volatile`은 이 목적에 **적합하지 않음**

### 센서별 주기 관리

```cpp
struct SensorSlot {
  const char* name;
  int period_ms;      /* each sensor has its own period */
  long next_due_ms;   /* when this sensor is due next */
};
```

- 각 센서의 다음 측정 시각을 기록해 **도래한 것만** 읽음
- 실패한 센서는 다음 주기에 재시도하고, 연속 실패 시 상태를 표시

---

## 데이터 표현 (Data Representation)

- 웹으로 내보낼 때는 **JSON**이 사실상 표준

```json
{
  "timestamp": 1735689600,
  "temperature": 23.4,
  "humidity": 45.0,
  "light": 512,
  "distance_cm": 87.5,
  "status": { "dht11": "ok", "cds": "ok", "hcsr04": "error" }
}
```

### 설계 시 고려할 점

- 측정 시각을 함께 보내면 **값이 언제 것인지** 알 수 있음
- 센서별 상태를 함께 보내면 브라우저에서 고장을 표시할 수 있음
- 실패한 센서 값은 **0이 아니라 null 또는 이전 값**으로 구분해 표현할 것
  - 0을 쓰면 "측정값 0"과 "측정 실패"를 구분할 수 없음

---

## 11장 정리 (Summary)

- 센서를 통합할 때의 핵심 문제는 **주기·소요 시간·실패의 차이**
- 하나의 루프에 모두 넣으면 가장 느린 센서가 전체를 지배함
- **수집 스레드와 서비스 스레드를 분리**하고, 공유 상태는 한 회차 전체를 뮤텍스로 보호
- 센서 인터페이스를 **추상화**하면 센서를 추가해도 수집 루프를 고치지 않아도 됨
- 데이터에는 **측정 시각과 센서별 상태**를 함께 담을 것
  - 실패를 0으로 표현하지 말 것
- 이 구조가 실습 14 미니 CCTV의 뼈대가 됨

> 다음 장에서는 센서 대신 카메라와 마이크를 다룸
