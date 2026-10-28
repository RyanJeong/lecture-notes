<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 4 - 센서 통합 웹 서버

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 4 - 목표 (Goals)

- **센서 통합**: 실습 3의 센서 3종을 **단일 프로그램**으로 통합 제어
- **스레드 분리**: 주기가 서로 다른 센서 수집 루틴을 **멀티스레드로 격리**
- **공유 자원 동기화**: **뮤텍스(Mutex)** 기반 임계 구역 보호 및 원자 변수의 한계 분석
- **웹 서비스 연동**: 실시간 수집 데이터를 **HTTP JSON API**로 클라이언트에 제공

### 통합 시 주요 해결 과제

| 문제 유형 | 발생 원인 및 시스템 영향 |
| :--- | :--- |
| **주기 차이** | DHT11 2초 주기 대비 초음파 센서의 고속 측정 요구 |
| **소요 시간** | DHT11 비트뱅잉 대기로 인한 수십 ms 단위 CPU 점유 |
| **센서 장애** | 특정 센서 통신 실패 시 전체 수집 루프 중단 방지 |

---

## 실습 4 - 구성 (Layout)

```text
mep/
├── common/
│   ├── gpio.hpp
│   └── signal_stop.hpp
└── lab04/src/
    ├── sensors.hpp          # the three routines written in lab 3
    ├── http.hpp             # the smallest server a browser will talk to
    └── 00_sensor_hub.cc     # integration: shared state and two loops
```

```bash
cd mep/lab04/src
clang++ -std=c++14 -Wall -Wextra -I../../common \
        00_sensor_hub.cc -o hub -lgpiod -llgpio -pthread
./hub
```

- **모듈 재사용**: 실습 3에서 작성한 센서 제어 루틴을 모듈화하여 재활용
- **스레드 링크**: POSIX 스레드 라이브러리 연동을 위해 `-pthread` 옵션 추가

[//]: # "INCLUDE: ./mep/13/src/sensors.hpp --reference"
[//]: # "INCLUDE: ./mep/13/src/http.hpp --reference"

---

## 실습 4 - 하나의 루프로는 안 되는 이유 (One Loop Fails)

```text
loop: read DHT11 (20 ms) -> read light (1 ms) -> read distance (30 ms)
      -> answer the browser -> sleep
```

- **응답성 저하**: DHT11 비트뱅잉(20ms) 중에는 HTTP 웹 요청 처리 불가
- **지연 누적**: 거리 센서 타임아웃(30ms) 발생 시 전체 수집 루프 주기 지연
- **병목 발생**: 가장 느린 센서의 동작 주기가 전체 시스템 주기를 지배

> 동작 주기가 다른 독립 작업은 스레드 기반 루프 분리가 필수

---

## 실습 4 - 두 개의 루프 (Two Loops)

| 스레드 | 주요 역할 및 담당 업무 | 실행 주기 |
| :--- | :--- | :--- |
| **수집 스레드** | 센서 데이터 계측 및 상태 갱신 | 0.5초 고정 주기 |
| **메인 스레드** | 클라이언트 HTTP 웹 요청 수신 및 응답 | 이벤트 기반 즉시 응답 |

- **자원 동기화**: 두 스레드가 동일한 센서 상태 구조체에 동시 접근하므로 보호 필요
- **생산자·소비자 패턴**: 센서 수집(쓰기)과 웹 서버 응답(읽기)으로 역할 명확히 분리

---

## 실습 4 - 왜 `atomic`이 아닌가 (Why a Mutex)

- **원자 변수의 한계**: 개별 필드가 `std::atomic`이어도 다중 필드의 일관된 동시 갱신은 보장 불가

```text
collector: writes temp=26 ... (preempted here) ... writes distance=15
web:       reads -> temp 26 (this sweep) + distance 8 (last sweep)
```

- **데이터 불일치**: 스레드 선점 발생 시 서로 다른 주기의 측정값이 뒤섞이는 현상 유발
- **뮤텍스 잠금**: 전체 센서 측정 스냅샷을 단일 임계 구역(Critical Section)으로 묶어 보호
- **`volatile` 부적합성**: 최적화 방지 기능만 제공할 뿐 스레드 동기화 및 메모리 배리어 미제공

---

## 실습 4 - 예제 코드 (Example)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --to 22"

- **테이블 주도 설계**: 채널명과 단위를 메타데이터 배열로 관리하여 센서 확장 용이

---

## 실습 4 - 공유 상태 (Shared State)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 23 --to 35"

- **공유 데이터 캡슐화**: 센서 측정값 배열과 동기화 뮤텍스를 단일 상태 구조체로 묶어 관리

---

## 실습 4 - 스냅샷 (Snapshot)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 36 --to 52"

- **락 점유 최소화**: 웹 스레드는 스냅샷 복사 후 즉시 뮤텍스를 해제하여 수집 지연 방지

---

## 실습 4 - 실패 격리 (Isolating Failures)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 53 --to 63"

- **오류 상태 플래그**: 채널별 수집 성공 여부(`ok`)를 관리하여 대시보드에 결측치(`--`) 표시
- **장애 격리**: 특정 센서 연결이 단절되어도 나머지 센서의 정상 수집 파이프라인 유지

---

## 실습 4 - JSON 만들기 (Building JSON)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 64 --to 83"

- **버퍼 안전성 검증**: `snprintf` 반환값(기록 시도 길이)을 검사하여 버퍼 오버플로 방지

---

## 실습 4 - 두 스레드 띄우기 (Starting the Threads)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 84 --to 104"

- **스레드 분기**: 백그라운드 수집 스레드(`std::thread`) 가동 후 메인은 HTTP 대기

---

## 실습 4 - 수락 루프 (Accept Loop)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 105 --to 118"

- **비차단 폴링**: `poll()` 타임아웃을 지정하여 요청 대기 중에도 정지 플래그를 주기적 감시

---

## 실습 4 - 종료 (Shutdown)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 119"

- **스레드 합류(`join`)**: 수집 스레드의 완전한 종료를 확인한 후 프로그램 자원 해제
- **댕글링 방지**: 스레드 종료 전 객체 소멸로 인한 메모리 오염 및 세그멘테이션 폴트 방지

---

## 실습 4 - 데이터 표현 (Data Representation)

- **웹 표준 형식**: 센서 데이터 직렬화를 위해 경량 텍스트 포맷인 **JSON** 규격 채택

```json
{
  "sweeps": 817,
  "sensors": [
    { "name": "temperature", "unit": "C", "value": 22.0, "ok": true },
    { "name": "distance", "unit": "cm", "value": 0.0, "ok": false }
  ]
}
```

- **상태 명시성**: 센서 실패를 `0`으로 모호하게 처리하지 않고 `ok: false` 필드로 구별

---

## 실습 4 - 확인 방법 (Checking It Works)

```bash
# Start the integrated sensor hub server
./hub

# Inspect network IP address and test the JSON endpoint
hostname -I
curl http://localhost:8080/api
```

- **웹 대시보드 검증**: 브라우저(`http://<IP>:8080/`) 접속 시 1초 주기로 자동 갱신
- **하드웨어 디버깅**: 값이 `--`로 표시될 경우 해당 센서의 전원 공급 및 배선 상태 점검

---

## 실습 4 - 과제 (Tasks)

1. **통합 동작 검증**: 센서 3종(DHT11, CdS, HC-SR04) 연결 후 4개 채널 동시 갱신 확인
2. **장애 격리 실험**: DHT11 배선 분리 후 조도 및 거리 센서의 정상 수집 여부 관찰
3. **수집 주기 변경**: 수집 주기를 100ms로 단축한 후 DHT11 체크섬 실패율 변화 측정
4. **타임스탬프 추가**: JSON 응답에 수집 시각(Timestamp) 필드를 추가하도록 구조 확장
5. **동시성 검증**: 복수 브라우저 동시 접속 시 스냅샷 데이터의 일관성 확인

### 고찰 항목

- **동기화 부재 영향**: 뮤텍스 잠금을 배제했을 때 관측되는 데이터 불일치 현상 분석
- **스레드 분리 필요성**: 단일 루프 구조 대비 멀티스레드 구조의 응답성 및 안정성 비교
