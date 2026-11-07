<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 하드웨어 접근과 동기화

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 하드웨어 접근에서 `volatile`의 역할

### The `volatile` Keyword

- **컴파일러에 알리는 것**: 각 `volatile` 접근은 관찰 가능한 동작이므로 임의로 생략하거나 합칠 수 없음
- **대표 용도**: 주변장치의 메모리 맵 입출력(MMIO) 레지스터처럼 프로그램 바깥에서 값이 바뀌는 대상
- **주의**: `volatile`만으로 일반 메모리의 캐시를 끄거나 스레드 동기화·CPU 메모리 순서를 보장하지 않음

---

## 컴파일러는 무엇을 하는가 (What the Optimizer Does)

- **최적화 원칙**: C++ 추상 기계 관점에서 **관찰 가능한 동작이 보존된다면** 코드를 자유롭게 재구성

| 최적화 기법 | 컴파일러 변환 동작 |
| :--- | :--- |
| **레지스터 캐싱** | 반복 읽기 변수를 레지스터에 적재 유지 |
| **죽은 저장 제거** | 이후 읽히지 않는 메모리 쓰기 동작 삭제 |
| **명령 재배치** | 상호 의존성이 없는 기계어 실행 순서 변경 |
| **루프 불변 이동** | 루프 내 불변 연산을 반복문 외부로 이동 |

- **시야의 한계**: 컴파일러는 소스 코드 문맥만 인지하며, 하드웨어·ISR·DMA에 의한 외부 변경은 감지 불가

---

## 최적화와 하드웨어의 충돌 (The Problem)

<!-- IMAGE [다이어그램] 컴파일러가 값을 레지스터에 캐시해 하드웨어 갱신을 놓치는 상황 (img/24-register-caching.png) -->

- **일반 최적화**: 메모리 버스 접근 오버헤드를 줄이기 위해 값을 범용 레지스터에 상시 캐싱
- **임베디드 충돌 시나리오**:
  - 하드웨어 주변장치가 상태 레지스터(Status Register) 비트를 직접 갱신
  - 인터럽트 서비스 루틴(ISR)이 백그라운드에서 전역 플래그를 비동기 수정
  - DMA 컨트롤러가 CPU 개입 없이 메모리 버퍼를 직접 갱신
- **문제 발생**: 레지스터에 캐시된 이전 값만 참조하여 하드웨어의 최신 변경 상태를 영구히 감지 불가

---

## 잘못된 예 (Broken Busy-Wait)

[//]: # "INCLUDE: ./mep/06/src/00_volatile_broken.cc --from 4 --to 15 --no-comment"

- 소스에서는 반복해서 읽지만 포인터가 `volatile`이 아니므로 컴파일러는 하드웨어의 비동기 갱신을 알 수 없음
- 최적화 결과, 읽기를 루프 밖으로 옮기거나 루프 자체를 제거할 수 있음

---

## 올바른 예 (Correct with `volatile`)

[//]: # "INCLUDE: ./mep/06/src/01_volatile_correct.cc --from 4 --to 12 --no-comment"

> `volatile` 객체 접근은 관찰 가능한 동작이므로 컴파일러가 임의로 제거하거나 병합할 수 없음

- **동작 보장**: 매 반복마다 주변장치 주소를 다시 읽는 접근을 생성
- **보장 범위**: 실제 MMIO 동작은 대상 플랫폼의 컴파일러와 하드웨어 규약에 맞는 주소·접근 폭으로 구현해야 함

---

## 최적화 결과 비교 (Compiler Output)

```bash
# Generate optimized assembly for the non-volatile and volatile examples
clang++ -O2 -S mep/06/src/00_volatile_broken.cc -o /tmp/broken.s
clang++ -O2 -S mep/06/src/01_volatile_correct.cc -o /tmp/volatile.s
```

| 코드 | 최적화 결과 예시 | 의미 |
| :--- | :--- | :--- |
| 일반 포인터 | 이 예제에서는 함수가 `ret`만 남음 | 읽기와 대기 루프가 모두 제거되어 MMIO를 관찰하지 못함 |
| `volatile` 포인터 | `ldr` 후 `tbz`로 루프 반복 | 매 반복 메모리를 다시 읽고 상태 비트를 확인 |

- 위 결과는 AArch64 Clang `-O2` 예시이며, 정확한 어셈블리는 컴파일러와 타깃에 따라 달라짐
- **핵심 비교**: 일반 포인터는 반복 읽기를 보장하지 않지만, `volatile` 포인터는 각 접근을 보존

---

## 일반 포인터의 최적화 결과 (Non-volatile Assembly)

```asm
WaitForTxReadyBroken:
    ret
```

- `ret`만 남아 함수가 즉시 반환
- 일반 메모리는 프로그램이 바꾸지 않는 한 값이 유지된다고 가정할 수 있어 읽기와 대기 루프를 제거
- **결과**: 소스 코드의 폴링이 사라져 하드웨어 상태를 기다리지 않음

---

## `volatile` 포인터의 최적화 결과 (Volatile Assembly)

```asm
WaitForTxReady:
.Lloop:
    ldr     w9, [x8]
    tbz     w9, #0, .Lloop
    ret
```

- `ldr`: 주변장치 주소에서 상태 값을 읽음
- `tbz`: 0번 비트가 0이면 `.Lloop`로 돌아가 다시 읽음
- 비트가 1이 되면 반복을 마치고 `ret`으로 반환
- **결과**: `volatile` 접근이 루프 안에 남아 하드웨어의 갱신을 다시 확인
- 레지스터 이름과 주소 준비 명령은 컴파일러·타깃에 따라 달라질 수 있음

---

## `volatile`의 실제 관찰 (Observing a Volatile Access)

[//]: # "INCLUDE: ./mep/06/src/06_signal_flag_demo.cc"

---

## 신호 플래그 실행과 적용 범위 (Signal Flag)

```bash
clang++ -O2 mep/06/src/06_signal_flag_demo.cc -o /tmp/v
/tmp/v
```

- **신호 안전성**: POSIX 신호 처리기에서 안전하게 갱신 가능한 표준 타입은 `volatile sig_atomic_t`로 제한
- **적용 한계**: 이 표준 보장은 일반 하드웨어 ISR이나 멀티스레드 공유 변수로 무조건 일반화 불가

---

## 임베디드의 세 가지 용도 (Three Canonical Uses)

### 1. 메모리 맵 입출력 레지스터 (MMIO)

[//]: # "INCLUDE: ./mep/06/src/02_mmio_register.cc --from 4 --to 10 --no-comment"

- **MMIO 레지스터 접근**: 연속 쓰기가 하드웨어 명령이므로 죽은 저장 제거(Dead Store Elimination) 방지
- **비동기 신호 처리기**: `volatile sig_atomic_t` 기반의 단일 완료 플래그 전달
- **하드웨어 상태 폴링**: 주변장치가 갱신하는 상태 레지스터의 비지 웨이트(Busy-Wait) 대기

---

## `volatile`이 하지 않는 것 (What It Does NOT Do)

> **`volatile`은 스레드 동기화 수단이 아님**

- **역할 한계**: 컴파일러의 레지스터 캐싱 및 접근 최적화만 억제할 뿐 멀티스레드 안전성 미제공
- **보장하지 않는 3대 항목**:
  - **원자성(Atomicity) 부재**: `++g_count`와 같은 읽기-수정-쓰기(RMW) 연산의 분할 실행 방지 불가
  - **메모리 배리어 부재**: CPU 하드웨어 차원의 비순차적 명령어 재배치 차단 불가
  - **스레드 안전성 부재**: 멀티스레드 간 동시 접근 시 정의되지 않은 동작(Data Race) 유발

[//]: # "INCLUDE: ./mep/06/src/03_volatile_is_not_atomic.cc --from 5 --to 8 --no-comment"

---

## `std::atomic` 사용 (Use `std::atomic`)

[//]: # "INCLUDE: ./mep/06/src/04_atomic_counter.cc --from 5 --to 9 --no-comment"

- **`std::atomic`의 역할**: 하드웨어 원자적 명령어 호출 및 CPU 메모리 순서화(Memory Ordering) 보장

---

## 스레드 간 플래그 (Inter-Thread Flag)

[//]: # "INCLUDE: ./mep/06/src/05_atomic_flag.cc --from 4 --to 14 --no-comment"

- **스레드 동기화 표준**: 멀티스레드 간 안전한 상태 전달 및 카운터 동기화 표준 메커니즘 제공

---

## 실행 가능한 원자 카운터 (Runnable Atomic Counter)

[//]: # "INCLUDE: ./mep/06/src/07_atomic_counter_demo.cc"

---

## 원자 카운터 실행 결과 (Atomic Counter Result)

```bash
# Build and execute multi-threaded atomic counter verification
clang++ -std=c++14 -O2 -pthread \
  mep/06/src/07_atomic_counter_demo.cc -o /tmp/mep06-atomic
/tmp/mep06-atomic
```

- **실행 결과 검증**: 4개 스레드가 각각 500,000회 동시 증가 시 정확히 2,000,000 도출
- **데이터 레이스 방지**: 일반 변수나 `volatile int` 사용 시 발생하는 카운트 유실 및 미정의 동작 원천 방지

---

## 메모리 순서 (Memory Ordering)

- **순서화 제어**: `std::atomic`은 연산의 원자성뿐만 아니라 하드웨어 **메모리 순서**를 함께 제어

| 메모리 순서 | 하드웨어 동작 및 보장 범위 |
| :--- | :--- |
| `relaxed` | 개별 원자 변수의 원자성만 보장(순서 제약 없음) |
| `acquire` | 후속 읽기·쓰기가 해당 load 이전으로 재배치 금지 |
| `release` | 이전 읽기·쓰기가 해당 store 이후로 재배치 금지 |
| `seq_cst` | 전역 순차 일관성 보장(모든 스레드가 동일 순서 관찰) |

- **Release-Acquire 동기화**: `release` store 이전에 기록된 데이터는 `acquire` load 이후에 가시성 보장
- **기본 순서 모델**: `std::atomic`의 기본값은 `seq_cst`이며 안전하나 아키텍처별 동기화 비용 발생

---

## 하드웨어 레지스터 접근 패턴 (MMIO Patterns)

```cpp
// Read-modify-write: manipulate individual bitfields
volatile uint32_t* const reg = reinterpret_cast<volatile uint32_t*>(0x3F200000);

*reg |= (1u << 3);    // Set bit 3
*reg &= ~(1u << 3);   // Clear bit 3
*reg ^= (1u << 3);    // Toggle bit 3
```

- **비원자적 RMW**: `*reg |= mask`는 읽기·수정·쓰기 3단계이므로 인터럽트 발생 시 데이터 오염 위험
  - 하드웨어 SoC가 제공하는 독립된 **SET/CLEAR 전용 레지스터** 활용 권장
- **부수 효과(Side-Effect)**: 읽기 동작만으로 상태가 지워지는 Read-to-Clear 레지스터 불필요 읽기 금지
- **순서 보장 한계**: `volatile`은 상호 다른 주변장치 레지스터 간의 엄격한 실행 순서를 보장하지 않음

---

## 판단 기준 (Decision Guide)

<!-- IMAGE [결정트리] volatile / std::atomic / 뮤텍스 선택 결정 트리 (img/25-volatile-decision.png) -->

| 대상 상황 | 권장 동기화 및 수식어 |
| :--- | :--- |
| **메모리 맵 I/O 레지스터(MMIO)** | `volatile uint32_t*` 포인터 사용 |
| **비동기 신호(Signal) 플래그** | `volatile std::sig_atomic_t` 사용 |
| **스레드 간 공유 플래그·카운터** | `std::atomic<T>` 원자 변수 사용 |
| **복합 공유 데이터 구조체** | `std::mutex` + 일반 변수 조합 사용 |
| **하드웨어 ISR 간 상태 공유** | 전용 원자 명령 또는 플랫폼 배리어 활용 |

- `volatile`: 컴파일러의 레지스터 캐싱 및 접근 최적화 억제
- `std::atomic`: CPU 하드웨어 원자성 및 메모리 순서(Memory Ordering) 보장
- **상호 배타적 원칙**: 두 메커니즘은 대체 관계가 아니며 목적에 따라 구분 적용

---

## 흔한 오해 (Common Misconceptions)

| 개발자 오해 | 실제 기술적 사실 |
| :--- | :--- |
| `volatile`은 스레드 안전성을 보장한다 | 원자성 및 메모리 배리어가 없어 동기화 불가 |
| `volatile`은 성능 향상을 유발한다 | 컴파일러 최적화를 억제하므로 오히려 지연 발생 |
| `std::atomic`이 `volatile`을 완전 대체한다 | 레지스터 직접 매핑(MMIO)에는 여전히 필수 |
| 싱글 코어 시스템에서는 데이터 경쟁이 없다 | 단일 코어에서도 하드웨어 ISR 선점 발생 가능 |

- **최소 범위 원칙**: 하드웨어 레지스터와 직접 결합된 최소한의 입출력 변수에만 국한 적용
- **스레드 동기화 표준**: 멀티스레드 공유 상태는 `std::atomic` 또는 `std::mutex` 전담 처리
- **보수적 설계**: 모호한 동기화 환경에서는 항상 더 높은 안전성(`seq_cst`, 락 획득) 우선 채택
