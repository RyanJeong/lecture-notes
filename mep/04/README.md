<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## 라이브러리 설계와 최적화

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 왜 라이브러리로 나누는가 (Why Libraries)

- 라이브러리 분리 목적: 재사용, 빌드 범위 제한, 공개 경계 설정, 독립 배포, 언어 연동

| 이유      | 효과                           |
| --------- | ------------------------------ |
| 재사용    | 여러 프로그램이 같은 기능 공유 |
| 빌드 시간 | 변경된 부분만 다시 컴파일      |
| 경계 설정 | 공개 API와 내부 구현 분리      |
| 독립 배포 | 라이브러리 단위 갱신           |
| 언어 연동 | C API를 통한 다른 언어 호출    |

### 라이브러리의 구성: 인터페이스와 구현

- **인터페이스**: 헤더 파일이 정의하는 공개 계약 — 변경 시 호출자에 영향
- **구현**: 공개 계약을 만족하는 내부 코드 — 계약 유지 범위에서 변경 가능

> 좋은 라이브러리 설계: **인터페이스 최소화, 구현 변경 가능성 확보**

---

## 연계 실습 - 03장의 실행 파일을 라이브러리로 분리

- 03장의 `hello_pi` 타깃을 출발점으로 사용
- `main()` 밖의 센서 변환 코드를 `sensors` 라이브러리로 이동
- 응용 프로그램은 공개 헤더만 포함하고 구현 파일은 직접 참조하지 않음

```text
mep04/
├── CMakeLists.txt
├── include/sensors/convert.hpp    # public API
├── src/convert.cc                 # private implementation
└── app/main.cc                    # consumer
```

> 목표: **같은 기능을 유지한 채 빌드 경계와 공개 경계를 분리**

---

## 연계 실습 - 공개 API와 구현

```cpp
// include/sensors/convert.hpp
#pragma once

float RawToCelsius(int raw);
```

- `app/main.cc`: `#include "sensors/convert.hpp"`만 사용
- 공개 헤더 변경은 소비자의 재컴파일 범위를 넓힘

---

## 연계 실습 - 구현은 라이브러리 내부에 유지

```cpp
// src/convert.cc
#include "sensors/convert.hpp"

float RawToCelsius(int raw) { return static_cast<float>(raw) * 0.1f; }
```

- 보정식·플랫폼 헤더·내부 헬퍼는 `src/`에 유지

---

## 연계 실습 - CMake 타깃으로 정적 라이브러리 만들기

```cmake
add_library(sensors STATIC src/convert.cc)
target_include_directories(sensors PUBLIC include)
target_compile_features(sensors PUBLIC cxx_std_14)

add_executable(sensor_app app/main.cc)
target_link_libraries(sensor_app PRIVATE sensors)
```

- `PUBLIC include`: 소비자에게 공개 헤더 경로만 전파

---

## 연계 실습 - 정적 라이브러리 빌드와 확인

```bash
cmake -S . -B build-static -DCMAKE_BUILD_TYPE=Release
cmake --build build-static --parallel
file build-static/sensor_app build-static/libsensors.a
```

---

## 연계 실습 - 공유 라이브러리로 전환하고 관찰하기

```cmake
add_library(sensors SHARED src/convert.cc)
set_target_properties(sensors PROPERTIES
  VERSION 1.0.0
  SOVERSION 1)
```

```bash
cmake -S . -B build-shared -DCMAKE_BUILD_TYPE=Release
cmake --build build-shared --parallel
readelf -d build-shared/sensor_app | grep NEEDED
readelf -d build-shared/libsensors.so.1.0.0 | grep SONAME
```

- `STATIC`만 `SHARED`로 바꾼 뒤 산출물과 `NEEDED` 항목 비교
- 공개 함수 시그니처 유지 상태에서 구현 변경 후 실행 여부 확인

---

## 정적 라이브러리 (Static Library)

![h:140 center](img/00-static-link.png)

- 컴파일된 오브젝트 파일의 아카이브(`.a`)
- 링크 시 필요한 오브젝트 코드가 실행 파일에 포함
- 실행 시 `.a` 파일 불필요

```bash
clang++ -std=c++14 -c sensors.cc -o sensors.o
ar rcs libsensors.a sensors.o
clang++ -std=c++14 main.cc -L. -lsensors -o app
```

---

## 정적 링크의 처리 순서

1. `sensors.cc`를 `sensors.o`로 컴파일
2. `ar`로 `libsensors.a` 생성
3. 링커가 해결되지 않은 심볼을 제공하는 오브젝트 추출
4. 추출한 코드가 실행 파일에 포함

- 참조되지 않는 오브젝트: 아카이브에서 추출되지 않아 실행 파일에 미포함

```text
main.o: SensorRead() reference
libsensors.a: SensorRead() definition
```

```bash
# Success: the archive resolves SensorRead() left undefined by main.o
clang++ main.o -L. -lsensors -o app
# found one unresolved symbol from main.o and resolved it from libsensors.a

# Failure: no unresolved symbol exists when the archive is scanned
clang++ -L. -lsensors main.o -o app
# undefined reference to SensorRead()
```

- 정적 아카이브 순서: **심볼을 참조하는 오브젝트 뒤**에 배치
  - 링커(Linker)의 순차 처리: 왼쪽에서 오른쪽, 필요 심볼만 아카이브에서 추출

---

## 정적 라이브러리의 장점과 비용

| 장점                         | 비용                            |
| ---------------------------- | ------------------------------- |
| 실행 파일 하나로 배포 가능   | 여러 실행 파일에 코드 중복 가능 |
| 적재 경로 문제 없음          | 수정 후 소비자 재링크 필요      |
| 파일 시스템 제약 환경에 적합 | 실행 파일 크기 증가 가능        |

- 같은 실행 파일의 여러 프로세스: 읽기 전용 코드 페이지 공유 가능
- 서로 다른 바이너리에 포함된 복사본: 별개

---

## 공유 라이브러리 (Shared Library)

![h:110 center](img/01-shared-link.png)

- 별도 파일로 배포되며 동적 링커가 프로그램 시작 시 또는 최초 호출 시 적재
- 실행 파일에는 필요한 공유 객체와 심볼 정보 기록

```bash
clang++ -std=c++14 -shared -fPIC \
  -Wl,-soname,libsensors.so.1 \
  sensors.cc -o libsensors.so.1.0.0
ln -s libsensors.so.1.0.0 libsensors.so.1
ln -s libsensors.so.1 libsensors.so
```

- `-fPIC`(Position-Independent Code): 임의의 적재 주소에서 실행 가능한 코드 생성

---

## 공유 객체의 세 이름

![h:150 center](img/18-soname-chain.png)

- ABI(Application Binary Interface): 별도 컴파일한 코드 사이의 이진 수준 계약

| 이름      | 예                    | 사용 시점                        | 관리 주체   |
| --------- | --------------------- | -------------------------------- | ----------- |
| 링커 이름 | `libsensors.so`       | 빌드 시 `-lsensors`              | 개발 패키지 |
| SONAME    | `libsensors.so.1`     | 실행 파일 `NEEDED`, 실행 시 탐색 | ABI 주 버전 |
| real name | `libsensors.so.1.0.0` | 실제 공유 객체 파일              | 개별 릴리스 |

- 링커 이름과 SONAME: real name을 가리키는 심볼릭 링크
- 실행 파일은 real name이 아니라 라이브러리의 `DT_SONAME`을 기록

---

## ELF와 동적 섹션

- ELF(Executable and Linkable Format): Linux 실행 파일·오브젝트 파일·공유 라이브러리의 파일 형식
- ELF 파일: 코드·데이터·심볼·적재 정보처럼 목적별 데이터를 여러 섹션에 기록
- 동적 섹션(dynamic section): 동적 링커가 적재·심볼 해석에 사용하는 항목 목록

```text
ELF shared library
├── .text, .data        program code and data
├── .dynsym             dynamic symbol table
├── .dynstr             dynamic string table
└── .dynamic            dynamic linker entries: DT_*
```

- `readelf -d`: `.dynamic`의 `DT_*` 항목을 읽기 쉬운 형태로 출력
- `DT_`: ELF 동적 섹션 항목을 나타내는 접두사

---

## ELF 동적 섹션 - `DT_SONAME`과 `DT_NEEDED`

```text
$ readelf -d libsensors.so.1.0.0
  (SONAME)  Library soname: [libsensors.so.1]

$ readelf -d app
  (NEEDED)  Shared library: [libsensors.so.1]
```

| 항목        | 기록 위치           | 의미                          |
| ----------- | ------------------- | ----------------------------- |
| `DT_SONAME` | 공유 객체           | 이 파일이 제공하는 ABI 이름   |
| `DT_NEEDED` | 실행 파일·공유 객체 | 실행 시 필요한 공유 객체 이름 |

- 링커: `libsensors.so`를 선택한 뒤 `DT_SONAME`을 소비자의 `DT_NEEDED`로 기록
- 동적 링커: 소비자의 `DT_NEEDED` 이름으로 적재 대상을 탐색

---

## 동적 링커의 라이브러리 선택 흐름

```text
Build time
  clang++ app.o -lsensors
  └── records libsensors.so DT_SONAME in app DT_NEEDED

Run time
  app DT_NEEDED: libsensors.so.1
  └── searches configured paths, ld.so.cache, and default paths
      └── follows the symbolic link and loads libsensors.so.1.0.0
```

- `libsensors.so`: 빌드 시 선택용 이름
- `libsensors.so.1`: 이미 빌드된 실행 파일의 ABI 요구 이름
- real name: 배포자가 교체하는 실제 파일
- 실제 검색 우선순위: `RPATH`·`RUNPATH`·`LD_LIBRARY_PATH` 설정에 따라 달라짐

---

## SONAME 유지 - 호환 릴리스 업데이트

```text
1.0.0 → 1.1.0 or 1.0.1
VERSION   1.0.0 → 1.1.0
SOVERSION 1     → 1

libsensors.so.1 ──> libsensors.so.1.0.0
                     ↓ package update and ldconfig
libsensors.so.1 ──> libsensors.so.1.1.0
```

- 기존 `app`의 `DT_NEEDED`는 계속 `libsensors.so.1`
- 패키지 관리자: 새 real name 설치, SONAME 링크·`ld.so.cache` 갱신
- 다음 실행부터 동적 링커가 새 real name을 적재
- 함수 내부 수정·버그 수정·기존 ABI를 보존한 함수 추가에 적용
- 실행 중인 프로세스: 기존 매핑 유지, 재시작 후 새 라이브러리 적재

---

## SONAME 증가 - ABI 비호환 릴리스

```text
1.x ABI                         2.x ABI
libsensors.so.1 ──> 1.1.0       libsensors.so.2 ──> 2.0.0
        ↑                                  ↑
    existing app                      newly linked app
```

- `SOVERSION 2` 설정: 새 real name에 `DT_SONAME=libsensors.so.2` 기록
- 기존 실행 파일: 요구 SONAME `.so.1` 유지, 기존 ABI 실행
- 새 빌드: `libsensors.so` 링크가 `.so.2`를 가리키면 `NEEDED=.so.2` 기록
- `.so.1` 제거: 기존 실행 파일의 적재 실패 원인

---

## 정적과 공유 - 배포와 비용 비교

| 관점      | 정적 라이브러리(`.a`)    | 공유 라이브러리(`.so`)           |
| --------- | ------------------------ | -------------------------------- |
| 코드 결합 | 링크 시 실행 파일에 포함 | `NEEDED` 기록 후 적재 시 해석    |
| 갱신      | 소비자 재링크 필요       | ABI 호환 시 재링크 없이 교체     |
| 자원      | 바이너리별 코드 복사본   | 여러 프로세스의 코드 페이지 공유 |
| 운영 비용 | 실행 파일 하나로 배포    | SONAME·검색 경로·공개 ABI 관리   |

- 정적 링크: 파일 시스템 제약 또는 단일 실행 파일 배포에 적합
- 공유 링크: 여러 앱의 코드 공유와 독립 패치 릴리스에 적합

---

## 공유 객체 적재와 점검

```bash
readelf -d ./app | grep NEEDED
readelf -d libsensors.so.1.0.0 | grep SONAME
file ./app libsensors.so.1.0.0
```

- `NEEDED`: 실행 파일이 요구하는 공유 객체
- `SONAME`: 라이브러리가 제공하는 ABI 이름
- `file`: 타깃 아키텍처와 ELF 클래스 확인

---

## 적재 실패의 원인

- 파일을 찾지 못함: 라이브러리 검색 경로 문제
- 필요한 `SONAME` 파일 부재: 요구 ABI 주 버전 미설치 또는 탐색 경로 문제
- 심볼 없음: 라이브러리 버전 또는 가시성 문제

```text
error while loading shared libraries:
libsensors.so.1: cannot open shared object file
```

- 실행 파일과 타깃 루트 파일 시스템 동시 점검

---

## 공유 라이브러리의 두 이진 계약

| 구분 | 계약 대상           | 질문                                               | 위반 시 결과            |
| ---- | ------------------- | -------------------------------------------------- | ----------------------- |
| PIC  | 코드와 적재 주소    | 어느 가상 주소에서도 같은 코드를 실행 가능한가     | 텍스트 재배치·적재 실패 |
| ABI  | 호출자와 라이브러리 | 별도 컴파일한 기계 코드가 같은 방식으로 통신하는가 | 링크 실패·오동작        |

- PIC(Position-Independent Code): **프로세스 메모리** 안에서 코드의 위치 독립성 보장
- ABI(Application Binary Interface): **번역 단위·라이브러리 경계**에서 이진 호환성 보장
- 둘 다 소스 코드가 아닌 컴파일 후 기계 코드의 성질

---

## PIC - `-fPIC`가 만드는 위치 독립 코드

```bash
clang++ -std=c++14 -fPIC -c sensors.cc -o sensors.o
clang++ -shared sensors.o -o libsensors.so
```

- `-fPIC`: Position-Independent Code 생성 옵션
- 절대 주소 대신 PC 상대 주소와 전역 오프셋 테이블(Global Offset Table, GOT) 사용
  - PIC는 PC 상대 주소 지정과 GOT/PLT 테이블 구조를 결합한 결과물
- ELF 기반 리눅스의 공유 라이브러리: `-fPIC` 사용

### PIC 목적

- 임의의 가상 적재 주소
- 읽기 전용 코드 페이지 공유
- 주소 공간 배치 난수화(Address Space Layout Randomization, ASLR)

---

## PIC - PC 상대 주소 지정, GOT, PLT

| 용어                 | 역할                                      | PIC에서의 사용                      |
| -------------------- | ----------------------------------------- | ----------------------------------- |
| PC 상대 주소 지정    | 런타임 PC + 링크 시 결정된 변위           | 라이브러리 내부 위치·GOT 슬롯 계산  |
| 전역 오프셋 테이블   | 런타임 주소를 담는 쓰기 가능 테이블       | 외부·가로채기 가능한 심볼 주소 보관 |
| 프로시저 연결 테이블 | GOT를 통해 외부 함수로 점프하는 코드 조각 | 외부 함수 호출과 지연 바인딩        |

- PC 상대 주소 지정(Program Counter-relative addressing): 현재 명령어 주소(PC) + 링크 시 결정된 변위(displacement)
  - 현재 명령어 주소: 실행 중인 현재 명령어의 가상 주소, 프로세스별 적재 기준 주소에 따라 달라짐
  - 링크 시 결정된 변위: 정적 링커가 라이브러리 내부 배치 후 코드에 기록하는 상수
- 전역 오프셋 테이블(Global Offset Table, GOT): 동적 링커가 프로세스별 실제 주소로 채움
- 프로시저 연결 테이블(Procedure Linkage Table, PLT): 함수의 실제 주소를 코드에 직접 기록하지 않는 호출 경로
  - 지연 바인딩(Lazy Binding): 프로그램 시작 시 함수가 최초 호출되는 순간에 주소를 바인딩하는 최적화 기법
  - 첫 호출 시 PLT stub 코드는 동적 링커를 호출하도록 유도하여 외부 함수의 실제 주소를 찾아 GOT 슬롯에 기록 및 실행
  - 이후 호출부터는 첫 호출 시 완성된 GOT 슬롯의 주소를 읽어 바로 외부 함수로 고속 점프(Jump) 및 실행

```text
hidden internal symbol : PIC code → PC-rel disp(to Symbol) → symbol address
external data symbol   : PIC code → PC-rel disp(to Data GOT) → GOT slot(.got) → address
external function call : PIC call → PLT stub → PC-rel disp(to Func GOT) → GOT slot(.got.plt)  function address
```

- 내부·숨김 심볼: PC 상대 변위만으로 직접 접근·호출 가능, 외부 심볼: 적재 시점(Load Time), 외부 함수: 지연 바인딩

---

## PIC - 두 적재 주소에서 같은 주소 계산

```text
library offsets: instruction = 0x1200, GOT slot = 0x4000
PC-relative displacement: 0x4000 - 0x1200 = 0x2e00

process A load base B = 0x7f20_4000_0000
PC = B + 0x1200 = 0x7f20_4000_1200
GOT = PC + 0x2e00 = 0x7f20_4000_4000

process B load base B = 0x7f91_8000_0000
PC = B + 0x1200 = 0x7f91_8000_1200
GOT = PC + 0x2e00 = 0x7f91_8000_4000
```

- 적재 기준 주소(load base): 동적 링커가 라이브러리 첫 적재 구간에 배정한 가상 주소
- ASLR: 프로세스마다 다른 load base 선택
- 정적 링커가 코드·GOT 슬롯의 라이브러리 내부 배치 후 `0x2e00`을 결정
- 명령어 바이트의 `0x2e00`은 두 프로세스에서 동일, 실행 중 PC만 다름
- 각 GOT 슬롯: 해당 프로세스의 실제 전역 변수·함수 주소를 보관

---

## PIC - non-PIC의 텍스트 재배치

```text
non-PIC instruction contains absolute address A = 0x4000_6000
actual address after load = load base B + 0x6000

dynamic loader patches .text: A <- B + 0x6000
  -> writes to code page
```

- 적재 기준 주소: 라이브러리 코드·데이터가 프로세스 가상 주소 공간에서 시작하는 주소
- 텍스트 재배치: 비PIC 코드에 들어 있는 절대 주소를 실제 적재 기준 주소에 맞춰 수정하는 작업

---

## PIC - 텍스트 재배치와 코드 페이지 공유

```text
PIC shared library
process A virtual .text ---\
process B virtual .text ----> one read-only physical page
process C virtual .text ---/

non-PIC text relocation at load time
process A: patch .text -> Copy-on-Write -> private physical page A
process B: patch .text -> Copy-on-Write -> private physical page B
```

- 가상 `.text` 매핑: 각 프로세스 주소 공간의 코드 페이지 연결
- 물리 코드 페이지: 파일 페이지 캐시에서 제공하는 실제 메모리 페이지
- PIC 적재: 코드 수정 없음 → 읽기 전용 물리 페이지 하나를 여러 프로세스가 공유
- non-PIC 적재: 절대 주소 재배치로 코드 쓰기 발생 → Copy-on-Write로 프로세스별 물리 페이지 생성
- GOT·전역 데이터: 쓰기 가능 영역이므로 PIC 여부와 관계없이 프로세스별 물리 페이지 사용
- 64비트 링커: 텍스트 재배치를 요구하는 비PIC 오브젝트의 .so 생성 거부 가능(해당 오브젝트 `-fPIC` 재컴파일 필요)

> PIC의 메모리 절감 대상: 여러 프로세스가 공유하는 라이브러리의 읽기 전용 코드 페이지

---

## ABI - API 선언과 이진 계약

```cpp
// public header, source-level API
int SensorRead(int channel, float* value);
```

| 구분 | 호출자가 아는 정보                         | 확인 시점   |
| ---- | ------------------------------------------ | ----------- |
| API  | 함수 이름, 매개변수 타입, 반환 타입        | 소스 컴파일 |
| ABI  | 심볼 이름, 전달 위치, 반환 위치, 타입 배치 | 링크·실행   |

- API 호환: 기존 소스 코드가 새 헤더로 다시 컴파일 가능
- ABI 호환: **재컴파일하지 않은** 기존 실행 파일이 새 라이브러리와 실행 가능

---

## ABI - AArch64 호출 계약 예시

- `x0`~`x7`: AArch64의 첫 8개 정수·포인터 전달인자용 64비트 레지스터
- `w0`~`w7`: 같은 레지스터의 하위 32비트 뷰, `int` 같은 32비트 정수 전달인자·반환값에 사용
- 이 예제의 반환 타입은 `int`: 성공·실패 상태를 `w0`으로 반환

```text
C++ declaration
  int SensorRead(int channel, float* value);

AArch64 caller                       AArch64 library function
  w0 = channel                  -->    reads int channel from w0
  x1 = value                    -->    writes float through pointer in x1
  expects int result in w0      <--    returns int status in w0

Itanium C++ ABI symbol: _Z10SensorReadiPf
```

- 호출 규약 불일치: 잘못된 레지스터·스택 위치에서 전달인자 해석
- 이름 맹글링 불일치: `undefined reference` 발생
- 클래스·구조체 배치 불일치: 링크 성공 후 잘못된 메모리 접근 가능
- C API(`extern "C"`): 이름 맹글링 노출 축소, C++ ABI 경계 단순화

---

## ABI가 깨지는 경우 (ABI Breakage)

![h:250 center](img/17-abi-break.png)

- 이전 바이너리: `height`를 두 번째 필드로 가정
- 새 라이브러리 교체 후 잘못된 값 읽기 가능
- 컴파일 오류 없는 오동작 가능

---

## ABI 노출을 줄이는 설계

- 공개 헤더에는 **전방 선언, 생성·사용·파괴 함수**만 둠
- 파일 디스크립터, 버퍼, 락, 구현 클래스는 라이브러리 내부에 둠

```c
// include/sensors/sensor.h: public contract for consumers
struct SensorCtx;

struct SensorCtx* SensorCreate(void);
int SensorRead(struct SensorCtx* context, float* out);
void SensorDestroy(struct SensorCtx* context);
```

```c
// src/sensor.c: implementation compiled only by the library
struct SensorCtx {
  int file_descriptor;
  void* sample_buffer;
  unsigned int calibration_revision;
};
```

- 호출자에 노출되는 정보: 포인터 타입뿐
- 내부 구조체에 필드를 추가해도 기존 호출자의 ABI는 유지
- 생성된 핸들은 반드시 같은 라이브러리의 `SensorDestroy()`로 해제

---

## CMake의 SONAME·버전·링크 생성

```cmake
set_target_properties(sensors PROPERTIES
  VERSION 1.0.0
  SOVERSION 1)
install(TARGETS sensors LIBRARY DESTINATION lib)
```

- `VERSION`: real name의 전체 릴리스 버전
- `SOVERSION`: 공유 객체의 `DT_SONAME` ABI 주 버전

```text
build output                     install/lib/
libsensors.so     -> .so.1       libsensors.so     -> .so.1
libsensors.so.1   -> .so.1.0.0   libsensors.so.1   -> .so.1.0.0
libsensors.so.1.0.0              libsensors.so.1.0.0
```

- `cmake --build`: 빌드 디렉터리에 real name과 심볼릭 링크 생성
- `cmake --install`: 설치 디렉터리에 같은 링크 구조 설치
- `VERSION`·`SOVERSION` 설정: 수동 `ln -s` 불필요

---

## ABI 변경과 SONAME - 릴리스 판단표

| 변경                         | 기존 실행 파일           | SONAME       |
| ---------------------------- | ------------------------ | ------------ |
| 함수 내부 보정식 수정        | 그대로 실행              | 유지         |
| 새 함수 추가                 | 기존 호출은 그대로 실행  | 유지         |
| 함수 삭제·시그니처 변경      | 링크 또는 호출 실패 가능 | 주 버전 증가 |
| 공개 구조체의 필드 배치 변경 | 컴파일 없이 오동작 가능  | 주 버전 증가 |

```cmake
set_target_properties(sensors PROPERTIES
  VERSION 2.0.0
  SOVERSION 2)  # increment only for ABI-breaking releases
```

- 판단 기준은 소스 호환성이 아니라 **이미 빌드된 소비자 실행 파일**
- 불투명 핸들 내부 변경은 위 표의 구조체 변경에 해당하지 않음

---

## 공개 헤더와 의존성

- 공개 헤더의 선언: 호출자의 컴파일 의존성
- 헤더 변경: 많은 번역 단위의 재컴파일 유발
- 내부 헬퍼·플랫폼 헤더: 구현 파일에 한정

```cpp
class Sensor {
 public:
  int ReadMilliCelsius() const;
};
```

### 전방 선언으로 의존성 줄이기

```cpp
class GpioDevice;

class Sensor {
 public:
  explicit Sensor(GpioDevice* device);
};
```

- 전방 선언 타입: 객체 크기·멤버 접근 불가

---

## 라이브러리 의존성의 방향

```text
application
  |
public API library
  |
platform adapter
  |
libgpiod / lgpio / Linux
```

- 상위 계층: 하위 계층 구현 세부 사항 비의존
- 플랫폼 의존 코드: 어댑터 계층에 집중
- 테스트: 어댑터 대체 구현 사용 가능

---

## C++ ABI와 C API 경계

- C++ 이름 맹글링: 컴파일러·표준 라이브러리 설정에 의존
- 예외, RTTI, `std::string`: ABI 경계 확대
- 서로 다른 툴체인으로 빌드한 C++ 객체: ABI 비호환 위험

```cpp
extern "C" {

int mep_sensor_open(int* handle);
int mep_sensor_read(int handle, float* value);
void mep_sensor_close(int handle);

}
```

- 이름 맹글링 없는 함수 이름 제공
- 예외 대신 상태 코드로 오류 전달

---

## 공개 심볼과 ABI 안정성 확인

```bash
nm -D --defined-only libsensors.so | sort
readelf -Ws libsensors.so | grep GLOBAL
```

- 공개 헤더와 공개 심볼 목록을 버전별 비교
- 구조체 크기·필드 배치 변경 여부 확인
- 이전 버전 실행 파일로 새 라이브러리 통합 시험
- 호환성 검증: 릴리스 전 수행

---

## 성능 측정과 기준선 (Performance Measurement and Baselines)

- 최적화 대상 선정 기준: **추측이 아닌 측정 결과**

```bash
time ./app
perf stat -r 10 ./app
perf record ./app
perf report
size build/libsensors.so
```

- `time`: 전체 실행 시간 확인
- `perf stat`: CPU 이벤트 반복 측정
- `perf record`: 시간이 소비된 함수 위치 확인

---

## 측정 항목과 기준선

| 항목          | 질문                                  |
| ------------- | ------------------------------------- |
| 처리량        | 단위 시간에 얼마나 처리하는가         |
| 지연 시간     | 한 작업이 끝날 때까지 얼마나 걸리는가 |
| 메모리        | 실행 중 얼마나 사용하는가             |
| 바이너리 크기 | 저장 공간을 얼마나 차지하는가         |

```text
commit: 1a2b3c
flags: -O2
input: 640 x 480 frame
median: 8.4 ms
binary: 184 KiB
```

- 입력·옵션·타깃 장치 동시 기록
- 최적화 전후: 같은 조건에서 비교

---

## 최적화 우선순위

1. 알고리즘과 데이터 이동량
2. 불필요한 I/O와 메모리 할당
3. 컴파일러 최적화 옵션
4. SIMD와 플랫폼 특화 명령

> 전체 실행 시간의 1% 구간을 절반으로 줄여도 전체 개선은 0.5%

---

## 최적화 수준 (Optimization Levels)

![h:170 center](img/19-opt-tradeoff.png)

| 상황        | 시작 옵션  | 확인 항목        |
| ----------- | ---------- | ---------------- |
| 디버깅      | `-O0 -g`   | 소스 수준 추적   |
| 일반 배포   | `-O2`      | 속도·크기 기준선 |
| 연산 커널   | `-O3` 후보 | 처리량·전력      |
| 플래시 제약 | `-Os`      | 크기·속도 손실   |

- 옵션 변경마다 같은 입력으로 재측정

---

## `-O3` 적용 전 확인

- 루프·연산의 실제 병목 여부 확인
- 코드 크기 증가의 명령 캐시 영향 확인
- 부동소수점 결과의 허용 오차 확인
- 디버깅 난이도 증가 허용 근거 확인

> `-O3`: 기본값이 아닌 측정 기반 후보

---

## LTO (Link-Time Optimization)

![h:150 center](img/20-lto.png)

- 일반 컴파일: 번역 단위별 독립 최적화
- LTO: 링크 시 여러 번역 단위를 함께 분석
- 파일 경계를 넘는 인라인·상수 전파 가능

```cmake
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)

if(ipo_supported)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
```

---

## LTO 적용 후 확인

- 링크 시간과 메모리 사용량 증가
- 디버거의 함수·변수 표시 변화
- 재현 가능한 빌드 결과
- 최적화 전후 기능 회귀 검사

```bash
time cmake --build build --clean-first
size build/libsensors.so
```

---

## 불필요한 코드 제거 (Dead-Strip)

![h:300 center](img/21-dead-strip.png)

- 선택 제거 조건: 함수·데이터의 별도 섹션 배치
- 등록 기반 초기화처럼 간접 참조하는 심볼: 보존 필요

```cmake
add_compile_options(-ffunction-sections -fdata-sections)
add_link_options(-Wl,--gc-sections)  # GNU ld
# macOS: -Wl,-dead_strip
```

---

## Dead-Strip 결과 확인

```bash
size app
nm -C app | grep UnusedHelper
```

- 제거 전후 바이너리 크기 비교
- 필요한 등록 함수 유지 여부 실행 시험
- 코드 크기 감소와 기능 회귀 동시 확인

---

## 심볼 가시성과 공개 심볼 점검

```cmake
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
```

```cpp
#define MEP_API __attribute__((visibility("default")))

extern "C" MEP_API int mep_sensor_read(int id, float* out);
```

- 외부 호출이 필요한 함수만 `default`로 표시
- 공개 ABI 표면: 의도한 선언으로 제한
- 동적 심볼·재배치 수 감소 시 적재 비용 감소 가능

---

## 공개 심볼 점검

```bash
nm -D --defined-only libsensors.so
readelf -Ws libsensors.so | grep GLOBAL
```

- 예상하지 않은 전역 함수·전역 변수 탐지
- 내부 헬퍼가 공개 ABI가 되는 상황 방지
- 릴리스 전 결과를 기준선과 비교

---

## Strip과 디버그 심볼 보관

![h:110 center](img/21-strip-size.png)

```bash
objcopy --only-keep-debug app app.debug
strip --strip-unneeded app
objcopy --add-gnu-debuglink=app.debug app
```

- 배포본 크기 축소
- 분석 시 동일 버전의 `app.debug` 파일 필요
- 디버그 파일: 빌드 산출물로 보관

---

## 라이브러리 설계와 최적화 점검표

| 단계 | 점검 항목                              | 확인 방법                     |
| ---- | -------------------------------------- | ----------------------------- |
| 설계 | 공개 헤더 최소화, 플랫폼 계층 격리     | 공개 선언과 내부 헤더 대조    |
| 배포 | API·ABI 변경 구분, `SONAME`·심볼 관리  | 이전 실행 파일 통합 시험      |
| 선택 | 정적·공유 링크를 배포 조건에 맞게 선택 | 설치 파일·의존성 목록 확인    |
| 측정 | 기준선·병목·바이너리 크기 기록         | 동일 입력의 반복 측정         |
| 적용 | LTO·dead-strip·가시성 비용 평가        | 빌드 시간·크기·기능 회귀 비교 |
| 검증 | 타깃 적재와 디버그 심볼 보관           | 타깃 실행·소스 버전 연결      |

> 순서: **설계 → 배포 계약 → 측정 → 최적화 적용 → 타깃 검증**
