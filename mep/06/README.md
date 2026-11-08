<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 하드웨어 접근과 동기화

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 하드웨어 접근에서 `volatile`의 역할

### The `volatile` Keyword

- **정의**: 프로그램 외부 요인에 의해 값이 바뀔 수 있는 객체임을 컴파일러에 알리는 타입 한정자
  - **외부 요인**: 프로그램의 실행 흐름과 무관하게 메모리의 값을 바꾸는 주체:
    - **주변장치 하드웨어**: 메모리 맵 입출력(MMIO) 레지스터의 값을 직접 갱신
    - **인터럽트 서비스 루틴(ISR)**: 메인 루프 실행 중에 끼어들어 공유 변수를 변경
  - **컴파일러에 대한 제약**: `volatile` 객체에 대한 읽기·쓰기를 생략·병합하지 않고 코드에 적힌 대로 수행
- **보장하지 않는 것**: 연산의 원자성, CPU의 메모리 접근 순서, 스레드 간 동기화

---

## 하드웨어 접근에서 `volatile`의 역할 (Cont'd - 1)

### 메모리 맵 입출력 (MMIO, Memory-Mapped I/O)

- **정의**: 주변장치의 레지스터를 CPU 메모리 주소 공간의 고정된 주소에 배치하는 방식
  - 예: GPIO, UART, SPI, I2C, PWM, 타이머 등 SoC(System on Chip)에 내장된 입출력 장치
- **접근 방법**: CPU가 RAM의 변수에 접근할 때와 같은 load·store 명령으로 주변장치 레지스터의 주소를 읽고 씀
  - 예: BCM2837(Raspberry Pi 3)의 GPIO 레지스터는 물리 주소 `0x3F200000`부터 배치

```text
CPU --LDR/STR addr--> [Bus: address decoder]
                        |-- 0x00000000-0x3EFFFFFF --> SDRAM (real memory)
                        `-- 0x3F000000-0x3FFFFFFF --> Peripheral registers
                                                      (GPIO, UART, Timer, ...)
```

- **상태 레지스터**: 주변장치 내부 회로가 값을 갱신하므로, CPU가 같은 주소를 다시 읽으면 다른 값이 나올 수 있음
  - 예: UART 송신 버퍼가 비면 회로가 "송신 가능" 비트를 1로 설정하고, CPU는 이 비트가 1이 될 때까지 반복해서 읽음
- **데이터·제어 레지스터**: CPU가 값을 쓰면 주변장치가 이에 반응하므로, 각 쓰기가 주변장치에 대한 명령으로 동작
  - 예: UART 데이터 레지스터에 `'O'`, `'K'`를 연속으로 쓰면 문자 2개를 차례로 전송

---

## 하드웨어 접근에서 `volatile`의 역할 (Cont'd - 2)

### 인터럽트 서비스 루틴 (ISR, Interrupt Service Routine)

- **인터럽트**: 버튼 입력, 타이머 만료, 데이터 수신 등의 사건 발생을 CPU에 알리는 하드웨어 신호
- **ISR**: 인터럽트 발생 시 CPU가 실행 중인 코드를 중단하고 호출하는 함수
- **ISR 플래그**: ISR이 사건 발생을 기록하고, 메인 루프가 이를 확인하는 공유 변수

[//]: # "INCLUDE: ./mep/06/src/08_isr_flag.cc --from 2 --to 13 --no-comment"

- **`volatile`이 없는 경우**: 루프 안에 플래그를 바꾸는 코드가 없으므로 컴파일러는 값을 불변으로 가정

---

## 하드웨어 접근에서 `volatile`의 역할 (Cont'd - 3)

### 관찰 가능한 동작 (Observable Behavior)

- **[as-if](https://en.cppreference.com/cpp/language/as_if) 규칙**: 컴파일러는 관찰 가능한 동작만 그대로 유지하면, 나머지 코드는 자유롭게 삭제·병합·재배치할 수 있음
- **관찰 가능한 동작**: 표준이 정한 보존 대상으로, 최적화 후에도 프로그램에 적힌 그대로 일어나야 함
  - `volatile` 객체에 대한 읽기·쓰기, 파일 기록, 터미널 입출력 등

| 구분 | 일반 객체 읽기·쓰기 | `volatile` 객체 읽기·쓰기 |
| :--- | :--- | :--- |
| **관찰 가능한 동작** | 아님 | 해당 |
| **as-if 변환** | 삭제·병합·재배치 가능 | 적힌 횟수·순서대로 실행 |
| **MMIO 레지스터** | 일부가 생략되어 전달되지 않을 수 있음 | 모두 하드웨어에 전달됨 |

- **`volatile`의 역할**: 최적화를 끄는 장치가 아니라, 어떤 읽기·쓰기가 보존 대상인지 컴파일러에 알리는 장치
  - 보존되는 것은 `volatile` 객체에 대한 읽기·쓰기뿐이며, 그 밖의 코드는 계속 최적화됨
- **근거**: C++14 (ISO/IEC 14882:2014) §1.9 — "Program execution"

---

## 하드웨어 접근에서 `volatile`의 역할 (Cont'd - 4)

### 예: UART로 문자열 "OK" 전송

[//]: # "INCLUDE: ./mep/06/src/09_uart_data_write.cc --from 4 --to 11 --no-comment"

- **`SendOkBroken()`**: 첫 번째 쓰기는 다시 읽히기 전에 덮어써지므로 죽은 저장 제거로 삭제되어 `'K'`만 전송
- **`SendOk()`**: 두 쓰기 모두 관찰 가능한 동작이므로 유지되어 `'O'`, `'K'` 순서로 전송
- **컴파일 결과**: AArch64 Clang `-O2`에서 `SendOkBroken()`은 `str` 1개, `SendOk()`는 `str` 2개 생성

---

## 컴파일러는 무엇을 하는가 (What the Optimizer Does)

- **대표적인 최적화 기법**: 모두 관찰 가능한 동작을 바꾸지 않는 범위에서 적용

| 최적화 기법 | 컴파일러의 변환 |
| :--- | :--- |
| **레지스터 캐싱** | 반복해서 읽는 변수를 메모리 대신 CPU 레지스터에 보관하여 재사용 |
| **죽은 저장 제거** | 다시 읽히기 전에 덮어써지는 메모리 쓰기를 삭제 |
| **명령어 재배치** | 서로 의존하지 않는 명령의 실행 순서를 변경 |
| **루프 불변 이동** | 반복마다 결과가 같은 연산을 루프 밖으로 이동 |

- **컴파일러의 한계**: 소스 코드에 나타난 변경만 인지하며, 하드웨어·ISR에 의한 변경은 알 수 없음

---

## 최적화와 하드웨어의 충돌 (The Problem)

![h:350 center](img/24-register-caching.png)

- **레지스터 캐싱**: 메모리 접근 횟수를 줄이기 위해 변수의 값을 레지스터에 보관하여 재사용
- **값이 외부에서 바뀌는 경우**:
  - 주변장치가 상태 레지스터(Status Register)의 비트를 갱신
  - ISR이 메인 루프와 공유하는 플래그를 변경
  - **DMA**(Direct Memory Access) 컨트롤러가 CPU를 거치지 않고 메모리 버퍼에 데이터를 기록
- **결과**: 레지스터에 보관된 이전 값만 참조하므로 바뀐 값을 끝내 읽지 못함

---

## 잘못된 예 (Broken Busy-Wait)

[//]: # "INCLUDE: ./mep/06/src/00_volatile_broken.cc --from 4 --to 15 --no-comment"

- **원인**: 포인터가 `volatile`이 아니므로 컴파일러는 루프 안의 상태 값을 불변으로 판단
- **결과**: 루프 진입 전에 한 번만 읽도록 변환하거나 대기 루프 자체를 삭제할 수 있음

---

## 올바른 예 (Correct with `volatile`)

[//]: # "INCLUDE: ./mep/06/src/01_volatile_correct.cc --from 4 --to 12 --no-comment"

> `volatile` 객체에 대한 읽기·쓰기는 관찰 가능한 동작이므로 컴파일러가 삭제하거나 병합할 수 없음

- **생성 코드**: 루프의 매 반복마다 레지스터 주소에서 값을 다시 읽는 load 명령 생성
- **주의**: 실제 MMIO 접근은 SoC 데이터시트에 명시된 주소와 접근 크기(예: 32비트)를 따라야 함

---

## 최적화 결과 비교 (Compiler Output)

```bash
# Generate optimized assembly for the non-volatile and volatile examples
clang++ -O2 -S 00_volatile_broken.cc -o /tmp/broken.s
clang++ -O2 -S 01_volatile_correct.cc -o /tmp/volatile.s
```

| 대상 코드 | 최적화 결과 | 동작 |
| :--- | :--- | :--- |
| **일반 포인터** | 함수 본문에 `ret`만 남음 | 대기 루프가 삭제되어 상태를 확인하지 않음 |
| **`volatile` 포인터** | `ldr`·`tbz` 루프 유지 | 매 반복마다 레지스터를 다시 읽어 상태 비트 확인 |

- **기준**: 라즈베리파이(AArch64)의 Clang `-O2` 결과이며, 세부 어셈블리는 컴파일러와 아키텍처에 따라 다름
- **핵심 차이**: 일반 포인터는 반복 읽기가 삭제되고, `volatile` 포인터는 모든 읽기가 유지됨

---

## 일반 포인터의 최적화 결과 (Non-volatile Assembly)

```asm
WaitForTxReadyBroken:
    ret
```

- **루프 삭제**: 대기 루프가 사라지고 즉시 반환하는 `ret`만 남음
- **컴파일러의 판단**: 프로그램이 값을 바꾸지 않으므로 상태 비트도 불변으로 가정
- **삭제 근거**: 부수 효과가 없는 무한 루프는 미정의 동작이므로 루프의 종료를 전제로 삭제
- **결과**: 송신 준비가 끝나기 전에 다음 코드를 실행

---

## `volatile` 포인터의 최적화 결과 (Volatile Assembly)

```asm
WaitForTxReady:
.Lloop:
    ldr     w9, [x8]
    tbz     w9, #0, .Lloop
    ret
```

- `ldr`: `x8`이 가리키는 레지스터 주소에서 32비트 값을 읽음
- `tbz`: 0번 비트가 0(송신 불가)이면 `.Lloop`로 분기하여 다시 읽음
- `ret`: 0번 비트가 1이 되면 루프를 빠져나와 반환
- **결과**: 매 반복마다 레지스터를 다시 읽으므로 하드웨어가 바꾼 값을 감지

---

## `volatile`의 실제 관찰 (Observing a Volatile Access)

[//]: # "INCLUDE: ./mep/06/src/06_signal_flag_demo.cc"

---

## 신호 플래그 실행과 적용 범위 (Signal Flag)

```bash
# Build and run the signal flag demonstration
clang++ -O2 06_signal_flag_demo.cc -o /tmp/v
/tmp/v
```

- **신호**(Signal): 운영체제가 프로세스에 보내는 비동기 알림(예: `alarm(1)`이 1초 뒤 보내는 `SIGALRM`)
- **실행 결과**: 1초 뒤 `Signal received; the loop stopped.`를 출력하고 종료
- **ISR과의 관계**: Linux 사용자 프로그램은 ISR을 직접 작성할 수 없으므로 신호 처리기로 같은 구조를 구현
- **신호 처리기 공유 변수**: 신호 처리기에서 값을 써도 안전하도록 표준이 정한 타입은 `volatile std::sig_atomic_t`
- **적용 범위**: 신호 처리기에 대한 보장이며, 스레드 간 동기화에는 적용되지 않음

---

## 임베디드의 세 가지 용도 (Three Canonical Uses)

### 예: GPIO 17 출력 설정 (MMIO)

[//]: # "INCLUDE: ./mep/06/src/02_mmio_register.cc --from 4 --to 10 --no-comment"

- **MMIO 레지스터**: 각 쓰기가 하드웨어 명령이므로 죽은 저장 제거(Dead Store Elimination) 대상에서 제외
- **신호 처리기 플래그**: 신호 처리기가 설정하고 메인 루프가 확인하는 `volatile std::sig_atomic_t` 변수
- **상태 폴링**: 주변장치가 갱신하는 상태 레지스터를 반복해서 읽는 비지 웨이트(Busy-Wait)

---

## `volatile`이 하지 않는 것 (What It Does NOT Do)

> **`volatile`은 스레드 동기화 수단이 아님**

- **역할**: 컴파일러가 읽기·쓰기를 생략하지 않도록 할 뿐, 스레드 안전성은 제공하지 않음
- **보장하지 않는 항목**:
  - **원자성(Atomicity)**: `++g_count`의 읽기-수정-쓰기(RMW)가 중간에 끊길 수 있음
  - **메모리 배리어**: CPU가 메모리 접근 순서를 바꾸는 것을 막지 못함
  - **스레드 안전성**: 여러 스레드가 동시에 접근하면 데이터 경쟁(Data Race)으로 미정의 동작 발생

---

## `volatile`이 하지 않는 것 (Cont'd - 1)

### 원자성 (Atomicity)

- **상황**: 두 스레드가 같은 카운터를 각각 한 번씩 증가시키므로 기대값은 2

[//]: # "INCLUDE: ./mep/06/src/03_volatile_is_not_atomic.cc --from 5 --to 8 --no-comment"

| 순서 | 스레드 A | 스레드 B | `g_count` |
| :--- | :--- | :--- | :--- |
| 1 | load → 0 | | 0 |
| 2 | | load → 0 | 0 |
| 3 | add, store → 1 | | 1 |
| 4 | | add, store → 1 | 1 |

- **원인**: `++g_count`는 load·add·store 3개 명령이며, 그 사이에 다른 스레드가 끼어들 수 있음
- **결과**: 증가 하나가 유실되어 최종값이 1
- **`volatile`의 한계**: 각 load·store를 보존할 뿐, 그 사이에 다른 스레드가 끼어드는 것은 막지 못함

---

## `volatile`이 하지 않는 것 (Cont'd - 2)

### 메모리 배리어 (Memory Barrier)

- **상황**: 생산자가 데이터를 쓴 뒤 준비 플래그를 세우고, 다른 코어의 소비자가 플래그를 확인한 뒤 데이터를 읽음

[//]: # "INCLUDE: ./mep/06/src/11_volatile_no_barrier.cc --from 5 --to 18 --no-comment"

- **컴파일러 수준**: 두 `volatile` 객체에 대한 쓰기 순서는 코드에 적힌 대로 유지
- **CPU 수준**: ARM은 쓰기가 다른 코어에 보이는 순서를 바꿀 수 있어, `g_ready == 1`인데 `g_data`는 0일 수 있음
- **메모리 배리어**: 앞뒤 메모리 접근의 순서를 CPU에 강제하는 명령(AArch64 `dmb`)으로, `volatile`은 이를 생성하지 않음

---

## `volatile`이 하지 않는 것 (Cont'd - 3)

### 스레드 안전성 (Thread Safety)

- **스레드 안전성**: 여러 스레드가 동시에 사용해도 결과가 올바르고 동작이 정의되는 성질
- **상황**: 스레드 A는 위치를 (0, 0)에서 (1, 1)로 옮기고, 스레드 B는 `g_x == g_y`가 항상 성립함을 가정

[//]: # "INCLUDE: ./mep/06/src/12_volatile_not_thread_safe.cc --from 5 --to 15 --no-comment"

- **중간 상태 노출**: `g_x`만 바뀌고 `g_y`는 아직 바뀌지 않은 순간에 읽으면 (1, 0)을 관찰
- **데이터 경쟁**: 동기화 없는 동시 읽기·쓰기는 `volatile`이어도 C++ 표준상 미정의 동작
- **해결**: 단일 변수는 `std::atomic`, 여러 변수를 함께 바꿔야 하면 `std::mutex`로 보호

---

## `std::atomic` 사용 (Use `std::atomic`)

[//]: # "INCLUDE: ./mep/06/src/04_atomic_counter.cc --from 4 --to 9 --no-comment"

- **`std::atomic`의 역할**: 원자적 읽기-수정-쓰기와 메모리 순서(Memory Ordering)를 함께 보장
- **`volatile`과의 차이**: 관찰 가능한 동작에 해당하는지와 보장 대상이 다름
  - `volatile`: 관찰 가능한 동작이며, 프로그램 외부의 하드웨어를 위해 읽기·쓰기를 적힌 횟수·순서대로 보존
  - `std::atomic`: 관찰 가능한 동작이 아니며, 프로그램 내부의 다른 스레드를 위해 원자성과 순서·가시성을 보장
  - 하드웨어는 C++ 스레드가 아니므로 `std::atomic`은 MMIO 접근에 `volatile`을 대신하지 못함

---

## 스레드 간 플래그 (Inter-Thread Flag)

[//]: # "INCLUDE: ./mep/06/src/05_atomic_flag.cc --from 4 --to 14 --no-comment"

- **용도**: 한 스레드가 설정한 플래그를 다른 스레드가 안전하게 확인하는 표준 방법

---

## 실행 가능한 원자 카운터 (Runnable Atomic Counter)

[//]: # "INCLUDE: ./mep/06/src/07_atomic_counter_demo.cc"

---

## 원자 카운터 실행 결과 (Atomic Counter Result)

```bash
# Build and execute multi-threaded atomic counter verification
clang++ -std=c++14 -O2 -pthread \
  07_atomic_counter_demo.cc -o /tmp/mep06-atomic
/tmp/mep06-atomic
```

- **실행 결과**: 4개 스레드가 각각 500,000회 증가시킨 결과가 정확히 2,000,000
- **비교**: 일반 `int`나 `volatile int`를 사용하면 증가가 유실되며, 데이터 경쟁으로 미정의 동작 발생

---

## 메모리 순서 (Memory Ordering)

- **메모리 순서 제어**: `std::atomic`은 원자성과 함께 다른 메모리 접근과의 순서를 제어

| 메모리 순서 | 보장 범위 |
| :--- | :--- |
| `relaxed` | 해당 변수 연산의 원자성만 보장하며 순서 제약 없음 |
| `acquire` | 이 load 이후의 읽기·쓰기를 load 앞으로 재배치하지 않음 |
| `release` | 이 store 이전의 읽기·쓰기를 store 뒤로 재배치하지 않음 |
| `seq_cst` | 모든 스레드가 모든 `seq_cst` 연산을 같은 순서로 관찰 |

- **Release-Acquire 동기화**: `release` store 이전에 쓴 데이터는 그 값을 읽은 `acquire` load 이후에 보임
- **기본 순서**: `std::atomic` 연산의 기본값은 `seq_cst`이며, 가장 안전하지만 아키텍처에 따라 비용이 큼

---

## 메모리 순서 (Cont'd - 1)

### `relaxed`: 이벤트 카운터 (Event Counter)

- **상황**: 여러 스레드가 수신한 패킷 수를 세고, 모든 스레드가 끝난 뒤 합계만 보고

[//]: # "INCLUDE: ./mep/06/src/13_relaxed_counter.cc --from 6 --to 14 --no-comment"

- **보장**: `fetch_add`가 원자적이므로 증가가 유실되지 않고 합계가 정확함
- **보장하지 않음**: 카운터와 다른 변수 사이의 메모리 접근 순서
- **주의**: 카운터 값으로 다른 데이터의 준비 여부를 판단할 수 없음
- **적합한 경우**: 통계·참조 횟수 증가처럼 값 자체만 중요하고 다른 데이터를 보호하지 않는 경우

---

## 메모리 순서 (Cont'd - 2)

### `release`·`acquire`: 데이터 전달 (Publishing Data)

- **상황**: `volatile`로는 실패했던 생산자·소비자 예제를 `std::atomic` 플래그로 수정

[//]: # "INCLUDE: ./mep/06/src/14_release_acquire.cc --from 7 --to 20 --no-comment"

- **`release` (2)·`acquire` (3)**: 쓰기 (1)은 (2) 뒤로 밀려나지 않고, 읽기 (4)는 (3) 앞으로 당겨지지 않음
- **동기화**: (3)이 `true`를 읽으면 (1)이 (4)에 보이므로, `g_data`가 일반 `int`여도 항상 42를 반환
- **생성 코드**(AArch64 Clang `-O2`): `stlrb`(Store-Release Register Byte), `ldarb`(Load-Acquire Register Byte)

---

## 메모리 순서 (Cont'd - 3)

### `seq_cst`(Sequentially-Consistent): 서로의 플래그 확인 (Checking Each Other's Flag)

- **상황**: 두 스레드가 각자 자기 플래그를 세운 뒤 상대 플래그를 확인하고, 상대가 없을 때만 임계 구역에 진입

[//]: # "INCLUDE: ./mep/06/src/15_seq_cst.cc --from 8 --to 19 --no-comment"

- **`release`·`acquire`일 때**: store가 뒤따르는 load보다 늦게 보일 수 있어 두 스레드 모두 `false`를 읽고 함께 진입
- **`seq_cst`일 때**: 네 연산이 하나의 전체 순서를 가지므로 적어도 한 스레드는 상대 플래그를 확인함
- **생성 코드**(AArch64 Clang `-O2`): 두 순서 모두 `stlrb`·`ldarb`로 같으므로 이 예제에서 `seq_cst`의 추가 비용 없음
- **주의**: 생성 코드가 같아도 C++ 표준은 `release`·`acquire`의 동시 진입을 막지 않으므로 `seq_cst`로 작성

---

## 하드웨어 레지스터 접근 패턴 (MMIO Patterns)

[//]: # "INCLUDE: ./mep/06/src/10_mmio_rmw.cc --from 4 --to 12 --no-comment"

- **비원자적 RMW**: `*kReg |= mask`는 읽기-수정-쓰기 3단계로 실행
  - 읽기와 쓰기 사이에 ISR이 같은 레지스터를 바꾸면 그 변경이 유실될 수 있음
  - SoC가 제공하는 **SET/CLEAR 전용 레지스터** 사용 권장(예: BCM2837의 `GPSET0`, `GPCLR0`)
- **읽기의 부수 효과**: 읽기만으로 값이 지워지는 Read-to-Clear 레지스터는 불필요하게 읽지 않음
- **컴파일러 수준 순서**: `volatile` 객체에 대한 읽기·쓰기 순서는 코드에 적힌 대로 유지
- **CPU·버스 수준 순서**: 메모리 배리어(AArch64 `dmb`)가 있어야 보장됨
  - `dmb`(Data Memory Barrier): AArch64 ISA의 기계어 명령으로, 앞뒤 메모리 접근의 순서를 강제
  - 예: `a = *kPeriA; asm volatile("dmb sy" ::: "memory"); b = *kPeriB;`
    - `dmb sy`: Data Memory Barrier - System

---

## 판단 기준 (Decision Guide)

![h:200 center](img/25-volatile-decision.png)

| 상황 | 권장 수단 |
| :--- | :--- |
| **MMIO 레지스터** | `volatile uint32_t*` 포인터 |
| **신호(Signal) 처리기 플래그** | `volatile std::sig_atomic_t` |
| **스레드 간 공유 플래그·카운터** | `std::atomic<T>` |
| **여러 변수로 이루어진 공유 데이터** | `std::mutex`로 보호하는 일반 변수 |
| **ISR과 메인 루프 간 공유 데이터** | `volatile` + 인터럽트 비활성화 구간 또는 원자 명령 |

- `volatile`: 컴파일러가 읽기·쓰기를 생략하거나 병합하지 않도록 함
- `std::atomic`: 원자성과 메모리 순서(Memory Ordering) 보장
- **구분 사용**: 두 수단은 서로를 대체하지 않으며 목적에 따라 선택
