<!-- _class: lead -->

# 마이크로임베디드프로그래밍

## CI/CD, 라이선스, 배포

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 이 장의 구성 (Contents)

| 주제                | 내용                                              |
| ------------------- | ------------------------------------------------- |
| CI/CD               | 커밋마다 빌드·테스트·검사를 자동으로 수행         |
| 소프트웨어 라이선스 | 오픈소스 구성요소를 배포할 때 지켜야 하는 의무    |
| 배포 파이프라인     | 릴리스 아티팩트를 라즈베리파이에 설치하고 실행    |

- **세 주제의 관계**: 자동으로 검증한 결과물을 라이선스 의무와 함께 장치에 배포하는 하나의 흐름

---

## 자동화의 출발점: 형상 관리 (Version Control)

- **형상 관리**: 소스 코드의 모든 변경을 작성자·시점·내용과 함께 기록하는 활동
- **도구**: 이 장의 예는 Git과 GitHub를 기준으로 함

| 개념                          | 의미                                                  |
| ----------------------------- | ----------------------------------------------------- |
| 커밋(commit)                  | 하나의 논리적 변경을 기록한 최소 단위                 |
| 브랜치(branch)                | 다른 작업과 독립적으로 커밋을 쌓는 작업 흐름          |
| 풀 리퀘스트(PR, Pull Request) | 브랜치를 `main`에 병합하기 전에 검토를 요청하는 절차  |
| 태그(tag)                     | 특정 커밋에 붙이는 고정 이름(예: 릴리스 버전 `v1.2.0`) |

---

## 자동화의 출발점: 형상 관리 (Version Control) (Cont'd - 1)

### 임베디드에서의 중요성

- **버전 추적**: 장치마다 설치된 소프트웨어 버전과 하드웨어 리비전의 조합을 기록
- **소스 복원**: 현장 장치가 보고한 버전의 태그로 당시 소스를 그대로 복원
  - 예: 장치가 `v1.2.0`을 보고하면 `git checkout v1.2.0`으로 장애 재현 환경 구성
- **아티팩트 연결**: 태그 하나에 릴리스 바이너리 하나를 대응시켜 배포본의 출처를 확인
- **형상 관리가 없는 경우**: 장치에 설치된 바이너리가 어느 소스에서 빌드되었는지 알 수 없음

---

## CI/CD란 (What CI/CD Is)

- **CI**(Continuous Integration, 지속적 통합): 커밋이 공유 저장소에 올라올 때마다 자동으로 빌드·테스트하는 방식
- **CD**(Continuous Delivery, 지속적 전달): 검증된 결과물을 언제든 배포할 수 있는 상태로 자동 준비하는 방식
  - 실제 배포 시점은 사람이 승인
- **CD**(Continuous Deployment, 지속적 배포): 승인 단계 없이 검증된 결과물을 운영 장치까지 자동 배포하는 방식
- **CI가 없는 경우**: 한 개발자의 PC에서만 빌드되는 코드가 병합된 뒤에야 다른 PC에서 실패

---

## CI/CD란 (What CI/CD Is) (Cont'd - 1)

### 필요성

- **환경 차이 축소**: 빌드 환경을 워크플로 파일에 명시하므로 모든 변경을 같은 조건에서 검증
- **조기 발견**: 오류를 원인 커밋 직후에 발견하므로 원인 범위가 커밋 하나로 좁혀짐
- **수정 비용 절감**: 발견이 늦을수록 그 사이에 쌓인 커밋이 많아 원인 추적이 어려워짐
- **인적 오류 축소**: 버전 태그·패키징·업로드 같은 릴리스 절차를 스크립트로 고정

> CI 서버에 라즈베리파이가 없어도 **크로스 컴파일과 단위 테스트**는 자동화할 수 있음

---

## GitHub Actions (GHA)

<!-- IMAGE [스크린샷] 워크플로 실행 결과 화면. 잡별 성공/실패 표시 (img/27-gha-run.png) -->

- **GitHub Actions**: GitHub 저장소에 내장된 CI/CD 실행 플랫폼
- **워크플로**(workflow): `.github/workflows/` 디렉터리의 YAML 파일 하나로 정의하는 자동화 절차
- **이벤트**(`on:`): 워크플로를 시작하는 사건(예: `push`, `pull_request`)
- **잡**(job): 러너 하나에서 순서대로 실행되는 스텝의 묶음이며, 잡끼리는 기본적으로 병렬 실행
- **스텝**(step): 셸 명령(`run:`) 또는 재사용 가능한 액션(`uses:`) 하나
- **러너**(runner): 잡을 실행하는 가상 머신
  - GitHub 호스티드 러너는 잡마다 새로 생성되고 잡이 끝나면 폐기되는 일회성(ephemeral) 환경

---

## GitHub Actions (GHA) (Cont'd - 1)

```yaml
name: CI
on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@11bd71901bbe5b1630ceea73d27597364c9af683 # v4.2.2
      - name: Configure
        run: cmake -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
      - name: Build
        run: cmake --build build -j
      - name: Test
        run: ctest --test-dir build --output-on-failure
```

- `actions/checkout`: 러너에 저장소 소스를 내려받는 공식 액션
- `ctest`: 테스트가 하나라도 실패하면 0이 아닌 종료 코드를 반환하므로 잡이 실패로 기록됨

---

## 빌드 매트릭스 (Build Matrix)

<!-- IMAGE [격자도식] build_type x simd x os 조합이 병렬 잡으로 전개되는 격자 (img/28-build-matrix.png) -->

- **빌드 매트릭스**: 여러 설정 값의 모든 조합마다 같은 잡을 복제하여 병렬로 실행하는 기능

```yaml
strategy:
  fail-fast: false
  matrix:
    build_type: [Debug, Release]
    simd: [on, off]
    os: [ubuntu-latest, macos-latest]
```

- **생성되는 잡**: 2 × 2 × 2 = 8개 잡이 각자 다른 러너에서 동시에 실행
- **값 참조**: 스텝에서 `${{ matrix.build_type }}`처럼 현재 조합의 값을 읽음
- `fail-fast: false`: 기본값(`true`)은 한 조합이 실패하면 나머지 잡을 취소하지만, `false`면 끝까지 실행

---

## 빌드 매트릭스 (Build Matrix) (Cont'd - 1)

### 매트릭스 검증 범위

- **SIMD 경로와 스칼라 경로**: 두 구현을 모두 컴파일·테스트하여 한쪽만 깨지는 경우를 발견
  - **SIMD**(Single Instruction, Multiple Data): 명령 하나로 여러 데이터를 동시에 처리하는 CPU 기능
  - **스칼라 경로**: SIMD를 쓰지 않고 데이터를 하나씩 처리하는 대체 구현
- **운영체제별 재현**: Linux와 macOS에서 같은 소스가 빌드되는지 확인
- **크로스 컴파일 잡**: 매트릭스에 arm64 조합을 추가하면 라즈베리파이용 바이너리도 매 커밋 생성

---

## 임베디드 CI의 특수성 (Embedded CI)

- **제약**: GitHub 호스티드 러너는 클라우드의 가상 머신이므로 라즈베리파이 같은 실제 장치가 연결되어 있지 않음
- **자체 호스팅 러너**(self-hosted runner): 사용자가 소유한 컴퓨터에 러너 프로그램을 설치하여 잡을 실행하는 방식

| 항목                        | CI 가능 여부                                        |
| --------------------------- | --------------------------------------------------- |
| 호스트용 컴파일             | 가능                                                |
| **크로스 컴파일(arm64)**    | 가능 — 3장의 툴체인 파일 사용                       |
| 하드웨어 비의존 로직 테스트 | 가능 — 단위 변환·계산 함수                          |
| 정적 분석·포맷 검사         | 가능                                                |
| 실제 GPIO 동작              | 호스티드 러너는 불가, 장치를 연결한 자체 호스팅 러너는 가능 |
| 센서 타이밍 검증            | 장치를 연결한 자체 호스팅 러너만 가능               |

---

## 임베디드 CI의 특수성 (Embedded CI) (Cont'd - 1)

### 하드웨어 접근 코드와 순수 로직의 분리

- **순수 로직**: GPIO·SPI 같은 장치를 건드리지 않고 입력값만으로 결과가 정해지는 함수
  - 예: 12장 실습 3-C의 `ToCm(echo_us)`는 에코 펄스 길이를 거리(cm)로 변환
  - 예: 12장 실습 3-B의 `AdcToVoltage(raw)`는 ADC 값(0~1023)을 전압(V)으로 변환
- **분리하지 않은 경우**: 센서 읽기와 변환이 한 함수에 있으면 센서가 없는 러너에서 테스트할 수 없음
- **분리한 경우**: 변환 함수만 따로 호출하여 호스트에서 테스트
  - 예: `ToCm(580)`이 약 9.9cm를 반환하는지 검사
- **수동 점검 목록**: 분리 후에도 남는 하드웨어 의존 부분은 장치에서 확인할 항목을 목록으로 관리

---

## 단위 테스트 (Unit Testing)

- **단위 테스트**: 함수 하나처럼 작은 단위를 독립적으로 호출하여 기대한 결과를 내는지 확인하는 테스트
- **GoogleTest**: Google이 개발한 C++ 테스트 프레임워크

```cpp
#include <gtest/gtest.h>

double RawToCelsius(int raw) { return raw / 100.0; }

TEST(SensorTest, ConvertsRawToCelsius) {
  EXPECT_NEAR(25.0, RawToCelsius(2500), 1e-6);
}
```

- `TEST(그룹, 이름)`: 테스트 하나를 정의하는 매크로
- `EXPECT_NEAR(기대값, 실제값, 허용오차)`: 두 실수의 차이가 허용오차 이하인지 검사
  - 실수 연산은 반올림 오차가 생기므로 `EXPECT_EQ` 대신 허용오차를 둔 비교를 사용

---

## GoogleTest 빌드 설정 (GoogleTest Build Setup)

```cmake
cmake_minimum_required(VERSION 3.14)
project(SensorTest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
include(CTest)
include(FetchContent)

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2)
FetchContent_MakeAvailable(googletest)

add_executable(sensor_test sensor_test.cc)
target_link_libraries(sensor_test PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(sensor_test)
```

---

## GoogleTest 빌드 설정 (GoogleTest Build Setup) (Cont'd - 1)

- `FetchContent`: 구성 단계에서 GoogleTest 소스를 지정한 태그(`v1.15.2`)로 내려받아 함께 빌드
  - 개발 PC와 러너에 GoogleTest를 따로 설치할 필요가 없음
- `GTest::gtest_main`: `main()` 함수를 제공하는 라이브러리이므로 테스트 파일에 `main()`을 쓰지 않음
- `gtest_discover_tests()`: 실행 파일 안의 `TEST`를 찾아 CTest 테스트로 하나씩 등록
- **실행**: `ctest --test-dir build --output-on-failure`
  - 결과: `100% tests passed, 0 tests failed out of 1`(g++ 11, CMake 3.x에서 확인)
- **용도**: 하드웨어가 없는 러너에서 변환·계산 로직을 호스트 컴파일러로 검증

---

## 커버리지 게이트 (Coverage Gate)

<!-- IMAGE [스크린샷] 커버리지 리포트 화면. 기준선 미달 시 실패 표시 (img/29-coverage-report.png) -->

- **코드 커버리지**(line coverage): 테스트를 실행하는 동안 한 번 이상 실행된 소스 줄의 비율
- **커버리지 게이트**: 커버리지가 정해 둔 최소 기준(예: 80%)보다 낮으면 CI 잡을 실패시키는 검사
- **측정 도구**
  - `--coverage`: GCC·Clang이 실행 횟수를 기록하는 코드를 삽입하는 옵션
  - `lcov`: 실행 기록(`.gcda` 파일)을 모아 `coverage.info`로 요약하는 도구
  - `genhtml`: `coverage.info`를 줄 단위로 색칠한 HTML 리포트로 변환하는 도구

> 높은 커버리지는 품질을 보장하지 않지만, 낮은 커버리지는 **검증 부족의 신호**임

---

## 커버리지 게이트 (Coverage Gate) (Cont'd - 1)

```bash
cmake -S . -B build-cov -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS=--coverage -DCMAKE_EXE_LINKER_FLAGS=--coverage
cmake --build build-cov --parallel
ctest --test-dir build-cov --output-on-failure
lcov --capture --directory build-cov --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/tests/*' \
     --output-file coverage.info
genhtml coverage.info --output-directory coverage-html
# Gate: fail the job when line coverage is below 80%
lcov --summary coverage.info 2>&1 |
  awk '/lines/ { sub("%", "", $2); exit !($2 >= 80) }'
```

- `lcov --remove`: 시스템 헤더(`/usr/*`)와 내려받은 GoogleTest(`_deps`)를 측정 대상에서 제외
- **마지막 명령**: 줄 커버리지가 80% 미만이면 `awk`가 종료 코드 1을 반환하여 잡 실패

---

## 두 개의 게이트 (Two Gates, Not One)

- **Codecov**: 커버리지 리포트를 업로드받아 커밋 간 추이와 PR별 변화를 보여 주는 외부 서비스
- **이중 적용**: 같은 기준선(예: 90%)을 **CI 내부 게이트**와 **Codecov 게이트**에 모두 설정

| 게이트  | 강점                                                | 한계                                         |
| ------- | --------------------------------------------------- | -------------------------------------------- |
| CI 내부 | 네트워크·토큰 없이 동작하므로 포크 저장소의 PR에서도 실행 | 절대 기준값 미달만 검사                      |
| Codecov | 기준 커밋 대비 **하락**을 탐지하고 PR에 코멘트로 표시 | 서비스 장애나 토큰 누락 시 검사가 수행되지 않음 |

- **기준값 관리**: 두 게이트의 기준값은 따로 설정하므로 같은 수치로 맞춰 둠
  - 기준값이 다르면 같은 커밋이 한 게이트는 통과하고 다른 게이트는 실패
- **실행 순서**: 리포트를 먼저 업로드한 뒤 게이트를 판정
  - 판정을 먼저 하면 실패한 커밋의 리포트가 남지 않아 원인을 확인할 수 없음

---

## 정직한 커버리지 (Honest Coverage)

- **제외 대상**: 직접 작성하지 않은 코드(시스템 헤더, 서드파티 라이브러리, 테스트 코드)
  - 예: 위 GoogleTest 예제는 제외 전 48.8%, `/usr/*`와 `_deps` 제외 후 100%(lcov 1.14에서 확인)
- **장치 I/O 코드**: GPIO·SPI를 다루는 코드는 러너에서 실행할 수 없어 커버리지가 낮게 측정됨
- **제외 원칙**: 러너에서 실행할 수 없는 코드만 제외하고, 그 코드는 장치에서 별도로 검증
- **공개 원칙**: 제외 전후 수치를 함께 공개하여 측정 범위를 숨기지 않음
  - 예: 전체 79.3%, 장치 I/O 제외 95.6% — 로직 코드와 장치 코드의 검증 범위를 함께 제시

---

## SBOM — 무엇이 들어 있는가 (Software Bill of Materials)

- **SBOM**(Software Bill of Materials): 배포물에 포함된 구성요소의 이름·버전·라이선스를 기계가 읽을 수 있게 정리한 목록
  - 제조업의 부품표(BOM)를 소프트웨어에 적용한 개념
- **표준 형식**
  - **CycloneDX**: 웹 보안 비영리 단체 OWASP가 관리하는 보안 중심 형식(예: `sbom.cdx.json`)
  - **SPDX**: Linux Foundation이 관리하는 라이선스 중심 형식(ISO/IEC 5962:2021)
- **용도**: 새 취약점이 공개되면 SBOM만 검색하여 영향받는 릴리스를 즉시 찾음
- **운영 정책**
  - 릴리스마다 SBOM을 함께 보관하고, CI와 릴리스 시점에 다시 검사
  - SBOM 생성이 실패하거나 지정한 심각도 이상의 CVE가 발견되면 빌드를 실패시킴

---

## CVE 스캔 (Vulnerability Scanning)

- **CVE**(Common Vulnerabilities and Exposures): 공개된 보안 결함에 부여하는 고유 식별자
  - 예: `CVE-2021-44228`(Log4Shell)은 Java 로깅 라이브러리 Log4j 2의 원격 코드 실행 결함
- **심각도**: CVSS(Common Vulnerability Scoring System) 점수(0~10)에 따른 등급이며, `HIGH`는 7.0~8.9점, `CRITICAL`은 9.0~10.0점
- **Trivy**: SBOM이나 디렉터리를 취약점 데이터베이스와 대조하는 오픈소스 스캐너

```yaml
- name: CVE scan (Trivy)
  uses: aquasecurity/trivy-action@ed142fd0673e97e23eac54620cfb913e5ce36c25 # v0.36.0
  with: { scan-type: sbom, scan-ref: sbom.cdx.json, exit-code: "1", severity: "HIGH,CRITICAL" }
```

- `exit-code: "1"`: `HIGH` 이상 취약점이 하나라도 있으면 스텝을 실패시킴
- **수정판이 없는 취약점**: 영향 범위와 완화 조치를 별도로 검토하고 기록
- **Python 의존성**: `pip-audit -r requirements.txt`로 같은 검사를 수행

---

## 액션 고정 (Pinning Actions)

- **문제**: `@v4`, `@master` 같은 태그·브랜치는 액션 저장소 소유자가 언제든 다른 커밋으로 옮길 수 있음
- **해결**: 검토한 커밋의 전체 SHA(40자리 16진수)로 고정하고, 사람이 읽을 버전은 주석으로 남김

```yaml
uses: aquasecurity/trivy-action@ed142fd0673e97e23eac54620cfb913e5ce36c25 # v0.36.0 (pinned)
uses: aquasecurity/trivy-action@master # mutable: avoid
```

- **위험**: 옮겨진 태그가 가리키는 미검토 코드가 저장소의 비밀값(토큰)에 접근한 상태로 실행됨
  - 예: 2025년 3월 `tj-actions/changed-files` 태그가 악성 커밋으로 옮겨져 CI 비밀값 노출(CVE-2025-30066)
- **주의**: 주석 태그(annotated tag)는 태그 객체 SHA가 아니라 그 태그가 가리키는 커밋 SHA로 고정
  - `git ls-remote <저장소> 'refs/tags/v0.36.0^{}'`로 커밋 SHA 확인
- **보안 도구도 고정 대상**: CVE 스캐너도 버전을 고정해야 같은 커밋에 대해 같은 결과를 재현할 수 있음

---

## 릴리스 자동화 (Automated Release)

### 태그 자동 생성

- **조건**: `main`에 들어온 커밋이 `CMakeLists.txt`의 `project(... VERSION x.y.z)`를 올리면 워크플로가 태그 생성

```bash
VERSION=$(grep -oP 'VERSION \K[0-9]+\.[0-9]+\.[0-9]+' CMakeLists.txt)
git tag "v${VERSION}" && git push origin "v${VERSION}"
```

- **권한**: 워크플로에서 태그를 푸시하려면 `permissions: contents: write`가 필요
- **주의**: 기본 토큰(`GITHUB_TOKEN`)으로 푸시한 태그는 다른 워크플로를 시작하지 않음
  - 같은 워크플로에서 릴리스 작업을 이어서 실행하거나, 별도 토큰(GitHub App 토큰 등)으로 푸시

---

## 릴리스 자동화 (Automated Release) (Cont'd - 1)

### 태그 푸시 후 작업

1. Release 모드로 빌드하고 `strip`으로 바이너리의 디버그 심볼 제거(크기 감소)
2. 라이브러리·공개 헤더·`LICENSE`·`NOTICE`를 zip 파일 하나로 묶음
3. 이전 태그 이후의 커밋 로그로 `CHANGELOG.md` 갱신(Keep a Changelog 형식)
4. GitHub Release를 발행하고 zip 파일을 첨부

- **Keep a Changelog**: 버전별로 `Added`, `Changed`, `Fixed` 등의 절을 두어 변경 내역을 정리하는 작성 규칙
- **`strip`의 부작용**: 심볼이 없어 장치에서 디버거로 함수 이름을 볼 수 없으므로 심볼 파일을 따로 보관

> `LICENSE`·`NOTICE`를 포함해야 하는 이유는 다음 절 **소프트웨어 라이선스**에서 다룸

---

## 라이선스 분류 (License Categories)

<!-- IMAGE [스펙트럼] 퍼미시브→약한/강한 카피레프트→네트워크 카피레프트 스펙트럼 (img/30-license-spectrum.png) -->

- **소프트웨어 라이선스**: 저작권자가 소프트웨어의 사용·수정·배포를 허락하는 조건
- **카피레프트**(copyleft): 수정본이나 결합물을 배포할 때 같은 라이선스로 소스를 공개하도록 요구하는 조건

| 분류                | 예시                          | 주요 의무                                                   |
| ------------------- | ----------------------------- | ----------------------------------------------------------- |
| 퍼미시브            | MIT, BSD-3-Clause, Apache-2.0 | 저작권 고지와 라이선스 문구 유지                            |
| 약한 카피레프트     | LGPL-2.1                      | 라이브러리 자체의 수정 소스 공개와 라이브러리 교체 가능성 보장 |
| 강한 카피레프트     | GPL-2.0, GPL-3.0              | 배포하는 파생 저작물 전체의 소스 제공                       |
| 네트워크 카피레프트 | AGPL-3.0                      | 수정본을 네트워크 서비스로 제공할 때도 소스 제공            |

---

## 라이선스 분류 (License Categories) (Cont'd - 1)

### 퍼미시브 (Permissive)

- **허용 범위**: 상용·독점 제품에 사용할 수 있으며 소스 공개 의무가 없음
- **주된 의무**: 저작권 고지와 라이선스 전문을 배포물에 포함
- **Apache-2.0의 추가 의무**: 구성요소에 `NOTICE` 파일이 있으면 배포물에 함께 포함

### 약한 카피레프트 (LGPL)

- **동적 링크**(`.so`): 사용자가 라이브러리만 교체할 수 있으므로 응용 프로그램 소스는 공개하지 않아도 됨
- **정적 링크**(`.a`): 사용자가 수정한 라이브러리로 다시 링크할 수 있도록 응용 프로그램의 오브젝트 파일 등을 제공해야 함

---

## 카피레프트 (Copyleft)

### 강한 카피레프트 (GPL)

- **적용 시점**: GPL 코드를 포함한 프로그램을 **배포**할 때 의무가 발생하며, 내부에서만 사용하면 발생하지 않음
- **의무**: 받는 사람에게 해당 버전 라이선스 조건에 따라 대응 소스(Corresponding Source)를 제공
  - **대응 소스**: 실행 파일을 다시 빌드하는 데 필요한 소스 코드와 빌드 스크립트 전체
- **예**: GPL 프로그램을 수정해 라즈베리파이 제품에 넣어 판매하면 수정한 소스를 구매자에게 제공
- **적용 범위**: 결합 방식(링크·별도 프로세스)과 배포 형태에 따라 달라지므로 배포 전 검토

### 네트워크 카피레프트 (AGPL-3.0)

- **AGPL-3.0 제13조**: 수정한 프로그램이 네트워크로 사용자와 원격 상호작용하면 그 사용자에게도 대응 소스를 제공
- **GPL과의 차이**: GPL은 바이너리를 배포하지 않으면 의무가 없지만, AGPL은 웹 서비스 제공만으로도 적용될 수 있음

> 모든 네트워크 사용에 일괄 적용되는 규칙이 아니므로 조항의 적용 조건과 대상 버전을 확인

---

## CCTV 프로젝트 영향 (Why It Matters Here)

<!-- IMAGE [다이어그램] AGPL 네트워크 조항이 웹 서비스 사용자까지 전파되는 경로 (img/31-agpl-network.png) -->

- **Ultralytics 패키지와 YOLOv8 모델**: AGPL-3.0과 유료 Enterprise 라이선스 중 하나를 선택하는 이중 라이선스
- **확인 대상**: 사용하는 패키지 버전과 모델 가중치 파일마다 라이선스 고지를 확인

### 구체적 결과

- **배포 시**: AGPL-3.0 조건에 따라 대응 소스를 제공하거나 상용 라이선스 계약을 검토
- **원격 서비스 시**: 수정한 프로그램이 웹 화면으로 원격 사용자와 상호작용하면 제13조 적용 여부를 검토
- **구성요소별 확인**: 모델 가중치·학습 데이터·코드의 라이선스가 각각 다를 수 있으므로 따로 확인

> 수업 과제와 제품화는 의무 범위가 다르므로 제품화 전에 법률 검토를 받음

---

## 실무 대응 (Practical Compliance)

### 준수하는 배포

- 각 구성요소의 조건에 따라 라이선스 고지와 전문을 배포물에 포함
- Apache-2.0 의존성의 `NOTICE` 파일을 함께 포함
- AGPL 구성요소는 대응 소스를 공개하거나 상용 라이선스를 확보

### 위반하는 배포

- 라이선스 파일 없이 바이너리만 배포
- 수정한 AGPL 프로그램을 네트워크로 제공하면서 대응 소스를 받을 방법을 제공하지 않음

### 대안 검토

- **퍼미시브 라이선스 대체재**: 같은 기능의 MIT·Apache-2.0 구성요소를 선택하면 소스 공개 의무가 사라짐
- **확인 시점**: 의존성 라이선스는 프로젝트 초기에 확인할 때 교체 비용이 가장 작음

---

## 라이선스 점검 방법 (Checking Licenses)

```bash
# List dependencies and their licenses
pip-licenses --format=markdown        # Python
cmake --build build --target licenses # if the project provides it

# Generate an SBOM (component inventory)
syft dir:. -o spdx-json > sbom.json
```

- `pip-licenses`: 설치된 Python 패키지의 이름·버전·라이선스를 표로 출력하는 도구
- `syft`: 디렉터리나 컨테이너 이미지를 분석하여 SBOM을 생성하는 도구

| 확인 항목           | 확인 방법                          |
| ------------------- | ---------------------------------- |
| 사용 구성요소       | SBOM 생성                          |
| 구성요소별 라이선스 | 각 저장소의 `LICENSE` 파일         |
| 상용 사용 가능 여부 | 라이선스 분류(퍼미시브·카피레프트) |
| 배포 첨부물         | 라이선스 전문, `NOTICE`            |

---

## 배포 파이프라인 개요 (Overview)

<!-- IMAGE [플로차트] 커밋→CI→크로스 컴파일→릴리스→배포→검증 전체 파이프라인 (img/32-deploy-pipeline.png) -->

- **배포 파이프라인**: 커밋 하나가 장치에서 동작하기까지의 단계를 자동으로 이어 실행하는 절차

```text
source commit
   -> CI: build + unit tests + coverage + vulnerability scan
   -> cross compile: produce the arm64 artifact
   -> release: version tag, CHANGELOG, publish artifacts
   -> deploy: send to the target device and install
   -> verify: confirm operation on the device, collect logs
```

- **단계 간 규칙**: 한 단계가 실패하면 다음 단계로 진행하지 않음
  - 예: 단위 테스트가 실패한 커밋은 크로스 컴파일·릴리스 단계에 도달하지 않음

---

## 아티팩트 구성 (Release Artifact)

- **아티팩트**(artifact): 빌드가 만들어 내는 배포용 결과 파일

| 항목                   | 포함 이유                               |
| ---------------------- | --------------------------------------- |
| 공유 라이브러리(`.so`) | 실행 파일이 실행 시점에 불러옴          |
| 공개 헤더(`.h`)        | 외부 프로그램이 라이브러리를 사용할 때 필요 |
| 실행 파일              | 응용 프로그램 본체                      |
| 라이선스 전문          | 라이선스가 요구하는 고지 의무           |
| `CHANGELOG`            | 버전별 변경 내역                        |
| 버전 정보와 해시       | 전송 중 손상·변조 여부 확인             |

- **해시 확인**: `sha256sum -c SHA256SUMS`로 내려받은 파일의 SHA-256 값이 발행 값과 같은지 검사

---

## 아티팩트 구성 (Release Artifact) (Cont'd - 1)

### 버전 표기

- **시맨틱 버저닝**(SemVer, Semantic Versioning): `MAJOR.MINOR.PATCH` 세 숫자로 변경의 호환성을 나타내는 규칙
  - **MAJOR**: 호환되지 않는 API 변경(C++ 라이브러리는 ABI 변경 포함)
  - **MINOR**: 기존 사용 코드를 깨지 않는 기능 추가
  - **PATCH**: 기존 사용 코드를 깨지 않는 버그 수정
- **ABI**(Application Binary Interface): 컴파일된 코드끼리 맞아야 하는 함수 이름·인자 전달 방식·구조체 배치 규칙
  - 예: 공개 구조체에 멤버를 추가하면 소스는 그대로 컴파일되어도 기존 실행 파일과 ABI가 맞지 않음
- **예**: `1.4.2`에서 버그 수정은 `1.4.3`, 기능 추가는 `1.5.0`, 호환성 파괴는 `2.0.0`

---

## 타깃 장치 배포 (Deploying to the Target)

### 직접 전송

```bash
scp build-pi/app build-pi/libsensors.so USER@HOST:~/project/
ssh USER@HOST 'sudo systemctl restart mep.service'
```

- `USER`와 `HOST`를 타깃 장치의 계정명과 주소로 바꿔 실행
- `scp`: SSH 연결로 파일을 복사하는 명령
- **공유 라이브러리 탐색**: 동적 로더는 실행 파일과 같은 디렉터리의 `.so`를 자동으로 찾지 않음
  - 그대로 실행하면 `error while loading shared libraries: libsensors.so`로 실패
  - 링크 시 `-Wl,-rpath,'$ORIGIN'`을 주면 실행 파일 위치에서 `.so`를 찾음(g++ 11에서 확인)
- **한계**: 수동 전송은 간단하지만 어떤 버전이 설치되었는지 기록이 남지 않음
- **실제 제품**: 패키지(`.deb`)나 컨테이너 이미지로 배포하여 버전과 의존성을 관리

---

## 서비스 등록 (systemd Service)

- **systemd**: Raspberry Pi OS에서 부팅 시 서비스를 시작하고 감시하는 서비스 관리자
- **유닛 파일**: 서비스 하나의 실행 방법과 시작 조건을 적은 설정 파일

```ini
# /etc/systemd/system/mep.service
[Unit]
Description=MEP Mini CCTV
Wants=network-online.target
After=network-online.target

[Service]
ExecStart=/home/pi/project/app
Restart=on-failure
User=pi

[Install]
WantedBy=multi-user.target
```

---

## 서비스 등록 (systemd Service) (Cont'd - 1)

```bash
sudo systemctl enable --now mep.service
journalctl -u mep.service -f      # follow the log
```

- `Wants=`·`After=network-online.target`: 네트워크 연결이 완료된 뒤에 서비스를 시작
  - `After=`만 쓰면 순서만 지정할 뿐 네트워크 대기 자체를 요청하지 않음
- `Restart=on-failure`: 프로세스가 0이 아닌 종료 코드나 시그널로 끝나면 자동으로 다시 시작
- `User=pi`: root가 아닌 일반 계정 권한으로 실행
- `WantedBy=multi-user.target`: 부팅 시 다중 사용자 모드에 진입하면 자동으로 시작
- `enable --now`: 부팅 시 자동 시작을 등록하고 지금 바로 시작
- `journalctl -u ... -f`: 해당 서비스의 로그를 실시간으로 출력

---

## 운영과 회복 (Operations and Recovery)

### 배포 후 확인 항목

- **자동 시작**: 장치를 재부팅한 뒤 `systemctl status mep.service`가 `active (running)`인지 확인
- **자동 재시작**: 프로세스를 강제로 종료한 뒤 `Restart=on-failure`로 다시 시작되는지 확인
- **SD 카드 수명**: 로그가 계속 쌓이면 쓰기 횟수가 늘어 SD 카드가 빨리 마모되므로 로그 크기 제한
- **자원 안정성**: CPU 사용률, 메모리 사용량, SoC 온도가 장시간 운용 중에 일정한지 확인

### 롤백 준비

- **롤백**(rollback): 업데이트에 문제가 생겼을 때 이전 버전으로 되돌리는 작업
- **이전 아티팩트 보관**: 직전 버전의 릴리스 파일을 장치나 서버에 항상 남겨 둠
- **절차 문서화**: 업데이트 실패 시 되돌리는 명령과 순서를 미리 문서로 작성

> 현장에 설치된 장치는 직접 접근하기 어려우므로 롤백 방법을 배포 전에 준비
