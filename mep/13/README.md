<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 실습 4 - 센서 통합 웹 서버

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 실습 4 - 목표 (Goals)

- **센서 통합**: 실습 3의 센서 3종(DHT11, CdS, HC-SR04)을 하나의 프로그램에서 읽음
- **스레드 분리**: 센서 수집과 웹 요청 처리를 서로 다른 스레드에서 실행
- **공유 데이터 보호**: 두 스레드가 함께 쓰는 측정값을 뮤텍스로 보호하고, 원자 변수로 부족한 이유 분석
- **웹 서비스**: 측정값을 HTTP로 요청하면 JSON 형식으로 응답

### 통합할 때의 문제

| 문제 | 원인과 영향 |
| :--- | :--- |
| **주기 차이** | DHT11은 2초에 한 번만 읽을 수 있지만 거리·조도는 더 자주 읽어야 함 |
| **소요 시간** | DHT11 한 번 읽기에 약 25ms(시작 신호 20ms + 40비트 수신 약 3~5ms) |
| **센서 장애** | 센서 하나가 응답하지 않아도 나머지 센서의 값은 계속 제공해야 함 |

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

- **`sensors.hpp`**: 실습 3의 세 센서 읽기 코드를 `Sensors` 클래스 하나로 모은 헤더(프로토콜은 12장과 같음)
- **`-pthread`**: `std::thread`가 사용하는 POSIX 스레드 지원을 켜는 옵션(컴파일·링크 모두 적용)
- **공용 헤더의 전체 코드**: 9장 부록 참조

[//]: # "INCLUDE: ./mep/13/src/sensors.hpp --reference"
[//]: # "INCLUDE: ./mep/13/src/http.hpp --reference"

---

## 실습 4 - 하나의 루프로는 안 되는 이유 (One Loop Fails)

```text
loop: read DHT11 (~25 ms) -> read light (< 1 ms) -> read distance (up to 90 ms)
      -> answer the browser -> sleep
```

- **응답 지연**: 센서를 읽는 동안(ECHO 시간 초과 시 100ms 이상)에는 브라우저의 연결 요청을 받지 못함
- **지연 누적**: 거리 센서가 반사파를 받지 못하면 시간 초과까지 기다리므로 다른 센서의 측정도 늦어짐
- **주기 흔들림**: 브라우저 요청을 처리하는 시간만큼 다음 측정이 늦어져 측정 간격이 일정하지 않음

> 주기가 다른 두 작업을 스레드로 나누면 한쪽의 대기가 다른 쪽을 막지 않음

---

## 실습 4 - 두 개의 루프 (Two Loops)

| 스레드 | 역할 | 실행 시점 |
| :--- | :--- | :--- |
| **수집 스레드** | 세 센서를 읽어 공유 상태 갱신 | 수집 후 0.5초 대기를 반복 |
| **메인 스레드** | 브라우저의 HTTP 요청에 응답 | 요청이 올 때마다 |

- **스레드**(thread): 한 프로세스 안에서 메모리를 공유하며 독립적으로 실행되는 실행 흐름
- **역할 분리**: 수집 스레드는 공유 상태에 쓰기만, 메인 스레드는 읽기만 수행
- **동기화 필요**: 두 스레드가 같은 측정값 배열에 동시에 접근할 수 있으므로 보호가 필요

---

## 실습 4 - 왜 `atomic`이 아닌가 (Why a Mutex)

- **원자 변수의 한계**: 필드 하나하나가 `std::atomic`이어도 여러 필드를 한꺼번에 바꾸는 동작은 원자적이지 않음

```text
collector: writes temp=26 ... (preempted here) ... writes distance=15
web:       reads -> temp 26 (this sweep) + distance 8 (last sweep)
```

- **선점**(preemption): OS가 실행 중인 스레드를 중간에 멈추고 다른 스레드를 실행하는 동작
- **결과**: 웹 스레드가 이번 측정의 온도와 지난 측정의 거리를 섞어서 읽음
- **뮤텍스**(mutex): 한 번에 한 스레드만 잠글 수 있는 잠금 객체
- **임계 구역**(critical section): 뮤텍스를 잠근 상태에서만 실행되는 코드 구간
  - 네 값을 모두 쓰는 동작과 모두 읽는 동작을 각각 하나의 임계 구역으로 묶어 섞임 방지
- **`volatile`이 맞지 않는 이유**: 최적화에 의한 접근 생략만 막고, 원자성과 스레드 간 메모리 순서는 보장하지 않음

---

## 실습 4 - 예제 코드 (Example)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --to 22"

- **채널 표**: `kNames`, `kUnits`의 인덱스 0~3이 측정값 배열의 인덱스와 같아 채널을 추가할 때 표만 늘리면 됨

---

## 실습 4 - 공유 상태 (Shared State)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 23 --to 34"

- **`Snapshot`**: 네 채널의 측정값·유효 여부 배열과 이를 보호하는 뮤텍스를 하나의 클래스로 묶음
- **`std::lock_guard`**: 생성 시 뮤텍스를 잠그고, 범위를 벗어나 소멸할 때 자동으로 해제하는 RAII 클래스
  - 예외나 `return`으로 함수를 빠져나가도 잠금이 남지 않음

---

## 실습 4 - 스냅샷 (Snapshot)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 36 --to 48"

- **`Read()`**: 잠근 상태에서 값을 호출자의 배열로 복사하고 곧바로 잠금 해제
  - 잠근 시간이 짧아 수집 스레드가 `Replace()`에서 기다리는 시간도 짧음
- **`mutable`**: `const` 멤버 함수인 `Read()`에서도 뮤텍스를 잠글 수 있게 함

---

## 실습 4 - 실패 격리 (Isolating Failures)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 50 --to 59"

- **센서별 유효 여부**: 각 센서의 성공 여부를 `valid[]`에 따로 기록하므로 한 센서가 실패해도 나머지 값은 유효
- **`valid[1] = valid[0]`**: 온도와 습도는 DHT11 한 번의 측정으로 함께 얻으므로 성공 여부도 같음
- **DHT11 측정 간격**: 수집은 약 0.5초마다지만 `ReadDht()`는 2초가 지났을 때만 실제로 측정
  - 2초가 지나지 않았으면 직전 측정 결과를 그대로 반환

---

## 실습 4 - JSON 만들기 (Building JSON)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 61 --to 78"

- **`snprintf()`의 반환값**: 버퍼가 부족해 잘린 경우에도 실제로 쓴 길이가 아니라 쓰려던 길이를 반환
- **검사하는 이유**: 잘린 본문보다 큰 값을 `Content-Length`로 보내지 않도록, 버퍼가 부족하면 -1 반환

---

## 실습 4 - 두 스레드 띄우기 (Starting the Threads)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 80 --to 98"

- **`std::thread`**: 생성과 동시에 람다를 새 스레드에서 실행하며, 메인 스레드는 다음 줄로 진행
- **참조 캡처**: `[&sensors, &snapshot]`으로 `main()`의 지역 객체를 참조하므로, 수집 스레드가 끝날 때까지 두 객체가 살아 있어야 함

---

## 실습 4 - 수락 루프 (Accept Loop)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 99 --to 116"

- **`Accept()`**: `poll()`로 최대 300ms만 기다리므로 요청이 없어도 0.3초마다 종료 플래그 확인
- **경로 구분**: 요청에 `/api`가 있으면 JSON, 그 외에는 대시보드 HTML로 응답

---

## 실습 4 - 종료 (Shutdown)

[//]: # "INCLUDE: ./mep/13/src/00_sensor_hub.cc --from 118"

- **`join()`**: 수집 스레드가 종료 플래그를 확인하고 끝날 때까지 기다림
- **`join()`이 없으면**: 실행 중인 스레드를 가진 `std::thread` 객체가 소멸할 때 `std::terminate()`가 호출되어 프로그램이 비정상 종료
  - 근거: C++14 (ISO/IEC 14882:2014) §30.3.1.3 — "thread destructor"
- **소멸 순서**: `join()` 이후에 `snapshot`, `server`, `sensors`가 생성의 역순으로 소멸하므로 수집 스레드가 해제된 객체에 접근하지 않음

---

## 실습 4 - 데이터 표현 (Data Representation)

- **JSON**(JavaScript Object Notation): 이름-값 쌍과 배열로 데이터를 표현하는 텍스트 형식으로, 브라우저의 JavaScript가 바로 해석할 수 있음

```json
{
  "sensors": [
    { "name": "temperature", "unit": "C", "value": 22.00, "ok": true },
    { "name": "distance", "unit": "cm", "value": 0.00, "ok": false }
  ]
}
```

- **실제 응답**: 네 채널(`temperature`, `humidity`, `light`, `distance`)을 공백 없이 한 줄로 출력
- **`ok` 필드**: 측정 실패 시 `value`는 0이므로, 실제 측정값 0과 실패를 `ok: false`로 구별

---

## 실습 4 - 확인 방법 (Checking It Works)

```bash
# Start the integrated sensor hub server
./hub

# Inspect network IP address and test the JSON endpoint
hostname -I
curl http://localhost:8080/api
```

- **`hostname -I`**: 라즈베리파이의 IP 주소 출력
- **웹 대시보드**: 같은 네트워크의 브라우저에서 `http://<IP>:8080/`에 접속하면 1초마다 값이 갱신됨
- **값 대신 `--`가 나오는 경우**: 해당 센서의 `ok`가 `false`이므로 전원과 배선 점검

---

## 실습 4 - 과제 (Tasks)

1. **통합 동작 확인**: 세 센서(DHT11, CdS, HC-SR04)를 연결하고 네 채널이 모두 갱신되는지 확인
2. **시각 추가**: JSON 응답에 측정 시각 필드를 추가

### 고찰 항목

- **동기화가 없을 때**: 뮤텍스 잠금을 제거했을 때 나타날 수 있는 데이터 불일치 분석
- **스레드 분리의 효과**: 하나의 루프 구조와 두 스레드 구조의 응답 시간과 안정성 비교

---

## 부록 - HTTP 서버 클래스 (HTTP Server Class)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --to 20"

- **소켓**(socket): 네트워크 통신의 양 끝점을 나타내는 파일 디스크립터로, `SOCK_STREAM`은 TCP 연결을 뜻함

---

## 부록 - HTTP 서버의 소켓 설정 (Socket Setup)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --from 21 --to 41"

---

## 부록 - HTTP 서버의 연결 대기와 자원 관리 (Listen and Cleanup)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --from 42 --to 59"

- **`bind()`**: 소켓에 포트 번호(8080)를 지정
- **`listen()`**: 연결 요청을 받는 상태로 전환하며, 대기 중인 요청을 최대 4개까지 보관

---

## 부록 - HTTP 서버의 연결 수락과 경로 확인 (Accept and Route)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --from 60 --to 80"

---

## 부록 - HTTP 서버의 응답 생성 (Building the Response)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --from 82 --to 94"

- **응답 형식**: 상태 줄, 헤더(`Content-Type`, `Content-Length`), 빈 줄(`\r\n\r\n`), 본문 순서
- **`Content-Length`**: 본문의 바이트 수로, 브라우저는 이 길이만큼 본문을 읽음

---

## 부록 - HTTP 서버의 전체 데이터 전송 (Sending All Bytes)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --from 96 --to 109"

- **부분 쓰기**: `write()`는 요청한 바이트 중 일부만 보내고 반환할 수 있으므로 모두 보낼 때까지 반복

---

## 부록 - 대시보드 (Dashboard)

[//]: # "INCLUDE: ./mep/13/src/http.hpp --from 111"

- **동작**: 1초마다 `/api`를 요청하여 받은 JSON으로 표를 다시 그림
- **실패 채널**: `ok`가 `false`인 채널은 값 대신 빨간색 `--` 출력
