# AUTHORING.md — 강의 자료 작성 가이드

이 문서는 이 저장소에 강의 자료를 추가하거나 수정할 때 따라야 하는 절차와 규칙을 정리한 것입니다.

- **새 과목을 개설**하는 경우 → §2
- 기존 과목에 **새 챕터를 추가**하는 경우 → §3
- 기존 자료를 수정하는 경우 → §4 이후의 규칙을 참고

강의 자료의 **문체·용어·조사·코드 정확성** 규칙은 각 과목의 `LECTURE.md`(`c/LECTURE.md`, `cpp/LECTURE.md`)에 있습니다. 이 문서는 그 규칙을 반복하지 않고, **디렉터리 구조·빌드 파이프라인·검증 절차**만 다룹니다.

---

## 1. 저장소 구조

이 저장소는 **과목(course) 하나 = 최상위 디렉터리 하나** 구조입니다. 디렉터리 이름은 해당 과목에서 다루는 언어를 사용합니다.

```text
lecture-notes/
├── build.sh                 # README.md -> temp.md -> temp.pdf 변환
├── check_and_release.sh     # 슬라이드 검증 후 release/ 로 배포
├── ci.sh                    # GitHub Actions 워크플로를 로컬에서 그대로 재현
├── clean.sh                 # 모든 과목의 생성물 일괄 정리
├── engine.js                # marp 엔진 (shiki 코드 하이라이팅)
├── theme.css                # 모든 과목이 공유하는 Marp 테마 (1024x768, 16px)
├── c/                       # 과목: 컴퓨터프로그래밍기초 (ANSI C)
│   ├── LECTURE.md           # 검토 지침
│   ├── check_syntax.sh      # 문법 검사
│   ├── formatter.sh         # 코드 포매터
│   ├── clean.sh             # 생성물 정리
│   └── 00/ ... 07/          # 챕터
└── cpp/                     # 과목: 객체지향프로그래밍 (C++14)
    ├── LECTURE.md
    ├── check_syntax.sh
    ├── formatter.sh
    ├── clean.sh
    └── 00/ ... 14/          # 챕터
```

### 1-1. 과목 디렉터리 인식 규칙

**최상위 디렉터리에 `check_syntax.sh` 가 있으면 과목으로 인식**됩니다. 이 규칙 하나로 `build.sh`, `clean.sh`, `ci.sh`, GitHub Actions 워크플로가 모두 새 과목을 자동으로 찾아냅니다.

즉, **과목을 추가할 때 스크립트나 워크플로 파일을 수정할 필요가 없습니다**(단, §2-4의 코드 블록 언어 매핑은 예외).

### 1-2. 챕터 디렉터리 구조

```text
c/07/
├── README.md      # 슬라이드 원본 (유일한 편집 대상, Git 추적됨)
├── src/           # 슬라이드에 삽입되는 실제 컴파일 가능한 소스
├── img/           # 슬라이드 이미지
├── deprecated/    # 더 이상 쓰지 않는 소스·이미지 보관 (빌드·검사 대상 아님)
├── temp.md        # build.sh 생성물 (gitignore)
└── temp.pdf       # build.sh 생성물 (gitignore)
```

- **`README.md` 만 직접 편집**합니다. `temp.md` / `temp.pdf` / `temp.pptx` 는 전부 생성물이며 `.gitignore` 대상입니다.
- 챕터 번호는 **두 자리 숫자**여야 합니다(`08`, `15`). 모든 스크립트가 `[0-9][0-9]` 글로브로 챕터를 찾습니다.

---

## 2. 새 과목 추가

새 과목 `python`(예시)을 개설한다고 가정합니다.

### 2-1. 디렉터리 생성

```bash
COURSE="python"
mkdir -p "${COURSE}"
```

### 2-2. 과목 전용 스크립트 3종 작성

기존 과목의 스크립트를 복사해 컴파일러·확장자·플래그만 바꾸는 것이 가장 빠릅니다.

```bash
cp c/check_syntax.sh c/formatter.sh c/clean.sh "${COURSE}/"
```

| 스크립트 | 필수 여부 | 수정할 부분 |
|---|---|---|
| `check_syntax.sh` | **필수** | 검사 도구, 대상 확장자, 검사 플래그 |
| `formatter.sh` | 권장 | 포매터 명령, 대상 확장자 |
| `clean.sh` | 권장 | 그대로 사용 가능 |

`clean.sh` 는 생성물 이름 기준으로 동작하므로 대개 수정 없이 재사용할 수 있습니다.

### 2-3. `check_syntax.sh` 가 지켜야 할 계약

이 스크립트는 `build.sh` 와 CI 양쪽에서 호출되므로 다음 동작을 반드시 지켜야 합니다.

| 항목 | 요구사항 |
|---|---|
| 인자 | 선택적 `DIR` 하나. 생략 시 `[0-9][0-9]` 챕터 전체를 검사 |
| 검사 경로 | `<스크립트 위치>/<DIR>/src` |
| 제외 대상 | 파일명에 `_part` 또는 `_ignore` 가 포함된 파일 |
| 종료 코드 | 오류가 하나라도 있으면 **0이 아닌 값** |
| 오류 기록 | `<스크립트 위치>/error_file_lists.txt` |
| `-h`, `--help` | 도움말 출력 후 종료 |

> `build.sh` 는 `DIR` 인자에 임시 디렉터리 이름을 넘겨 **슬라이드에 삽입된 소스만** 검사합니다. 따라서 `DIR` 인자 처리를 빠뜨리면 빌드가 실패합니다.

### 2-4. 코드 블록 언어 매핑 확인 (유일한 예외)

`build.sh` 는 삽입 파일의 확장자로 마크다운 코드 블록의 언어를 결정합니다. 새 과목이 아래에 없는 확장자를 쓴다면 `build.sh` 의 `case` 문에 한 줄을 추가해야 합니다.

| 확장자 | 코드 블록 언어 |
|---|---|
| `.c` `.h` `.i` | `c` |
| `.cpp` `.cc` `.cxx` `.hpp` | `cpp` |
| `.py` | `python` |
| `.sh` | `bash` |
| `.java` | `java` |
| `.js` | `javascript` |

확장자가 목록에 없으면 언어 태그 없이 렌더링되어 **문법 강조가 적용되지 않습니다**.

### 2-5. `LECTURE.md` 작성

과목별 검토 지침입니다. `c/LECTURE.md` 또는 `cpp/LECTURE.md` 를 복제한 뒤 다음을 과목에 맞게 고칩니다.

- §0 언어 표준(허용 문법, 금지 문법)
- §1 용어 일관성 표
- §3-2 식별자·키워드 발음 및 조사 표
- §5 코드 정확성 체크리스트
- §6 내용 정확성 체크리스트

§2 괄호 규칙, §3-1 조사 기본 원칙, §4 마크다운 서식, §7 어색한 표현, §8 검토 절차는 과목과 무관하므로 **그대로 유지**합니다.

### 2-6. 첫 챕터 추가 및 확인

§3 절차로 `00/` 을 만든 뒤, 과목이 자동 인식되는지 확인합니다.

```bash
./ci.sh --help          # "Available courses:" 에 새 과목이 보여야 함
./ci.sh python          # 해당 과목만 빌드/검증
```

### 2-7. 새 과목 체크리스트

- [ ] `<course>/check_syntax.sh` 작성 및 §2-3 계약 준수
- [ ] `<course>/formatter.sh`, `<course>/clean.sh` 배치
- [ ] `<course>/LECTURE.md` 작성
- [ ] 새 확장자를 쓴다면 `build.sh` 의 언어 매핑에 추가(§2-4)
- [ ] `./ci.sh --help` 출력에 과목이 나타나는지 확인
- [ ] 첫 챕터 `00/` 빌드 및 검증 통과

---

## 3. 새 챕터 추가

### 3-1. 디렉터리 생성

```bash
COURSE="c"   # 대상 과목
CH="08"      # 기존 최대 번호 + 1

mkdir -p "${COURSE}/${CH}/src" "${COURSE}/${CH}/img"
```

### 3-2. `README.md` 뼈대 작성

첫 슬라이드는 `_class: lead` 로 가운데 정렬 표지를 만듭니다. 슬라이드 구분자는 `---` 입니다.

```markdown
<!-- _class: lead -->
# 컴퓨터프로그래밍기초

## Structures

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 첫 번째 주제

- 본문 내용

---

## 두 번째 주제 (Cont'd - 1)

- 이어지는 내용
```

- Marp 프론트매터(`marp: true` 등)는 사용하지 않습니다. 테마·크기는 `build.sh` 가 `--theme theme.css` 로 주입합니다.
- 표지 다음 슬라이드부터는 `##` 를 슬라이드 제목으로 사용합니다.
- 한 주제가 여러 슬라이드로 이어지면 제목에 `(Cont'd - 1)`, `(Cont'd - 2)` 를 붙입니다. 두 장뿐이면 번호 없이 `(Cont'd)` 만 붙이기도 합니다.

### 3-3. 소스 코드 추가

`src/` 아래에 **그 자체로 컴파일 가능한** 파일을 둡니다.

```text
c/08/src/00_struct_basic.c
c/08/src/01_struct_pointer.c
c/08/src/_snippet.c          # 슬라이드용 짧은 조각 모음
```

- 파일명은 `NN_설명.<확장자>` 형태의 두 자리 접두사를 사용합니다.
- `_snippet.*` 은 슬라이드에서 **줄 범위로만 잘라 쓰는** 조각 모음용 관례 파일입니다.
- 파일명에 `_part` 또는 `_ignore` 가 포함되면 문법 검사에서 **제외**됩니다.
- 의도적으로 컴파일되지 않아야 하는 예제(e.g., 댕글링 참조 시연)는 `#if 0` 으로 감쌉니다. §5-2 참조.

### 3-4. 이미지 추가

```text
c/08/img/00-struct-layout.png
```

- `NN-설명.png` 형태로 두 자리 접두사를 붙여 슬라이드 등장 순서를 유지합니다.
- 슬라이드에서는 상대 경로와 `center` 크기 지정자를 씁니다.

```markdown
![center h:420](img/00-struct-layout.png)
```

`h:` 값은 슬라이드 높이(768px) 대비 여백을 고려해 조정합니다. §6-2의 77% 규칙을 넘지 않아야 합니다.

### 3-5. 코드 삽입 플레이스홀더

슬라이드에 코드를 넣을 때는 코드 블록을 직접 쓰지 않고 **`INCLUDE:` 플레이스홀더**를 사용합니다.

```markdown
[//]: # (INCLUDE: ./c/08/src/00_struct_basic.c)
```

- 경로는 **저장소 루트 기준**입니다(`./c/08/src/...`).
- 이 방식 덕분에 슬라이드의 코드와 실제 컴파일되는 코드가 절대 어긋나지 않습니다. **코드를 슬라이드에 직접 붙여넣지 마십시오.**

전체 문법은 §4 참조.

### 3-6. 빌드 및 검증

```bash
COURSE="c"; CH="08"

# 1. 빌드 (INCLUDE 치환 + 문법 검사 + PDF 생성)
./build.sh "${COURSE}/${CH}/README.md" \
           "${COURSE}/${CH}/temp.md" \
           "${COURSE}/${CH}/temp.pdf"

# 2. 검증 및 배포 (슬라이드 넘침 검사 + 금지 패턴 검사 + pptx 생성)
./check_and_release.sh "${COURSE}/${CH}/temp.pdf"
```

편집 중에는 `loop` 인자를 붙여 1초 주기로 자동 재빌드할 수 있습니다.

```bash
./build.sh c/08/README.md c/08/temp.md c/08/temp.pdf loop
```

VS Code `Run on Save` 확장을 쓰면 `README.md` 저장 시 자동 빌드됩니다(설정은 `.vscode/settings.json` 참조).

### 3-7. 문체·내용 검토

빌드가 통과하면 해당 과목의 `LECTURE.md` 로 원고를 검토합니다.

```text
c/LECTURE.md를 기반으로 c/08/README.md를 검토해 주십시오.
```

검토는 §8-1의 3단계(형식 → 문장·표현 → 코드·내용) 순서로 수행하며, 수정 후 파일 전체를 다시 읽고 반복합니다.

### 3-8. 새 챕터 체크리스트

- [ ] `<course>/<NN>/` 디렉터리와 `src/`, `img/` 생성
- [ ] `README.md` 표지 슬라이드(`<!-- _class: lead -->`) 작성
- [ ] 코드는 `src/` 에 컴파일 가능한 형태로 두고 `INCLUDE:` 로 삽입 (직접 붙여넣기 금지)
- [ ] 이미지는 `img/NN-설명.png`, 슬라이드에서 `![center h:NNN](img/...)`
- [ ] `./build.sh` 통과 (문법 검사 포함)
- [ ] `./<course>/check_syntax.sh <NN>` 로 챕터 전체 소스 검사
- [ ] `./check_and_release.sh` 통과 (77% 규칙, 금지 패턴)
- [ ] 해당 `LECTURE.md` 기준 3단계 검토 완료
- [ ] `temp.*` 생성물이 커밋에 포함되지 않았는지 확인

---

## 4. `INCLUDE:` 플레이스홀더 레퍼런스

```text
[//]: # (INCLUDE: <경로> [--from N] [--to M] ... [--no-comment] [--reference])
```

### 4-1. 옵션

| 옵션 | 의미 |
|---|---|
| `--from N` | N번째 줄부터 삽입 |
| `--to M` | M번째 줄까지 삽입 |
| `--no-comment` | 슬라이드 연결 주석을 넣지 않음 |
| `--reference` | 코드 블록을 만들지 않고 **문법 검사용으로만** 파일을 등록 |

`--reference` 는 컴파일에 필요하지만 슬라이드에는 싣지 않을 파일(헤더 등)에 사용합니다.

```markdown
[//]: # (INCLUDE: ./c/05/src/alloc/alloc.h --reference)
```

### 4-2. 줄 범위 조합 규칙

`--from` / `--to` 는 등장 순서대로 짝을 이루며, 여러 구간을 이어 붙일 수 있습니다.

| 표기 | 결과 |
|---|---|
| (옵션 없음) | 파일 전체 |
| `--to 10` | 1 ~ 10행 |
| `--from 5 --to 10` | 5 ~ 10행 |
| `--from 5` | 5행 ~ 파일 끝 |
| `--from 5 --to 8 --from 12 --to 15` | 5~8행과 12~15행을 이어 붙임 |
| `--from 5 --from 12` | 5행~끝, 12행~끝 두 구간 |

긴 코드를 두 슬라이드로 나누는 표준 패턴은 다음과 같습니다.

```markdown
## 주제 (Cont'd - 1)

[//]: # (INCLUDE: ./cpp/12/src/17_type_erasure.cc --to 14)

---

## 주제 (Cont'd - 2)

[//]: # (INCLUDE: ./cpp/12/src/17_type_erasure.cc --from 16)
```

### 4-3. 슬라이드 연결 주석 자동 삽입

`--no-comment` 없이 줄 범위를 지정하면, 코드가 여러 슬라이드에 나뉜다는 표시가 자동으로 붙습니다.

| 조건 | 삽입되는 주석 |
|---|---|
| `--from` 개수 >= `--to` 개수 | 맨 위에 `/* continued from previous slide */` |
| `--to` 개수 >= `--from` 개수 | 맨 아래에 `/* continues on next slide */` |

이 주석 쌍으로 이어진 코드는 `LECTURE.md` 검토 시 **불완전한 코드로 보고하지 않습니다**.

### 4-4. 자동 처리 동작

- 옵션 없이 파일 전체를 삽입하면 `DO NOT CONTAIN THIS LINE IN THE MARKDOWN` 이 포함된 줄은 제거됩니다. **줄 범위를 지정한 경우에는 제거되지 않으므로**, 해당 표식이 범위 안에 들어가지 않도록 주의하십시오.
- 파일 끝의 빈 줄은 잘라냅니다.
- CR(`\r`) 은 제거됩니다.
- **참조한 파일이 없으면** `// Warning: File ... not found; creating empty file.` 이 삽입되고 빈 파일이 생성됩니다. 빌드는 통과하지만 `check_and_release.sh` 가 이 문구를 잡아 배포를 막습니다. 경로 오타의 신호입니다.

---

## 5. 문법 검사

### 5-1. 검사 대상

문법 검사는 두 단계로 나뉩니다.

| 단계 | 대상 | 실행 시점 |
|---|---|---|
| 빌드 중 검사 | 슬라이드에 **파일 전체로 삽입된** 소스와 `--reference` 로 등록된 파일 | `build.sh` |
| 전체 소스 검사 | `<course>/*/src/` 아래 **모든 파일** | `<course>/check_syntax.sh`, CI |

`build.sh` 는 대상 경로(`<course>/<NN>/`)를 보고 해당 과목의 `check_syntax.sh` 를 자동으로 선택합니다.

> **중요**: 줄 범위로 잘라 삽입한 조각은 그 자체로 컴파일되지 않으므로 빌드 중 검사에서 제외됩니다. 검사 대상 파일은 **원본 그대로** 임시 디렉터리에 복사되며, 슬라이드용으로 잘라내거나 표식을 제거한 버전이 아닙니다. 따라서 챕터 전체를 확실히 검증하려면 `<course>/check_syntax.sh <NN>` 을 직접 실행하십시오.

### 5-2. 의도적으로 컴파일되지 않는 예제

세그먼테이션 오류·댕글링 참조처럼 **일부러 잘못된 코드**를 보여줘야 할 때는 `#if 0` 으로 감싸고 표식을 답니다.

```c
#if 0  /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
int& Foo() {
  int temp = 10;
  return temp;  /* 지역 변수 참조 반환 */
}
#endif /* DO NOT CONTAIN THIS LINE IN THE MARKDOWN */
```

- 실제 파일은 `#if 0` 덕분에 문법 검사를 통과합니다.
- 슬라이드에는 표식이 달린 두 줄이 제거된 상태로 출력됩니다.

### 5-3. 프로젝트(Makefile) 검사

`src/` 아래에 `Makefile` 이 있으면 `check_syntax.sh` 가 `make` 로 빌드까지 검증한 뒤 `make clean` 합니다. 이 검사는 모든 파일이 존재하는 **실제 `src/` 트리에서만** 수행됩니다.

---

## 6. 빌드 파이프라인

```text
README.md
   │  build.sh
   │   1) [//]: # (INCLUDE: ...) 치환 -> temp.md
   │   2) 삽입된 소스를 임시 디렉터리로 원본 그대로 수집
   │   3) 해당 과목의 check_syntax.sh 실행 (실패 시 빌드 중단)
   │   4) marp + engine.js + theme.css -> temp.pdf
   ▼
temp.md, temp.pdf
   │  check_and_release.sh
   │   1) 각 페이지 내용 높이 <= 77% 검사
   │   2) 금지 패턴 검사
   │   3) release/<course>/<NN>.pdf 복사
   │   4) marp --pptx -> release/<course>/<NN>.pptx
   ▼
release/c/08.pdf, release/c/08.pptx
```

### 6-1. 검증 기준 (`check_and_release.sh`)

| 검사 | 실패 조건 |
|---|---|
| 슬라이드 내용 영역 | 페이지 내용 높이가 슬라이드 높이의 **77%** 초과 |
| 빈 파일 경고 | `temp.md` 에 `// Warning: File ... not found; creating empty file.` 존재 |
| 금지 표식 | `temp.md` 에 `DO NOT CONTAIN THIS LINE IN THE MARKDOWN` 존재 |

### 6-2. 77% 초과 시 해결 방법

- 슬라이드를 둘로 나누고 제목에 `(Cont'd - N)` 추가
- 코드는 `--from` / `--to` 로 나눠 삽입(연결 주석이 자동으로 붙음)
- 이미지의 `h:` 값 축소

> `check_and_release.sh` 는 **상대 경로**를 전제로 동작합니다(`c/08/temp.pdf`). 절대 경로를 넘기면 산출물이 `release/<절대경로>/` 아래에 생성됩니다.

---

## 7. 로컬 CI

`ci.sh` 는 GitHub Actions 워크플로를 로컬에서 한 번에 재현합니다. 전체 소스 검사 → 모든 챕터 빌드 → 검증 → 산출물 수집까지 수행하며, 중간에 실패해도 멈추지 않고 마지막에 요약을 출력합니다.

```bash
./ci.sh                 # 모든 과목
./ci.sh cpp             # 특정 과목만
./ci.sh --docker        # Linux 컨테이너에서 실행 (macOS 필수)
./ci.sh --help          # 사용법 및 인식된 과목 목록
```

> **macOS 주의**: `check_and_release.sh` 는 GNU 전용 옵션(`grep -oP`)과 ImageMagick 을 사용하므로 macOS 기본 환경에서는 동작하지 않습니다. `--docker` 옵션을 사용하십시오. 필요한 이미지는 최초 1회 자동으로 빌드됩니다.

> **macOS 문법 검사 주의**: 문법 검사는 **Linux/GCC 기준**입니다. macOS SDK 헤더는 `-ansi` 를 지정해도 POSIX 심볼을 노출하므로, TCPL 예제의 `getline` 처럼 표준 라이브러리와 이름이 겹치는 코드가 macOS 에서만 충돌로 보고될 수 있습니다. 강의 자료의 오류가 아닙니다.

---

## 8. 스크립트 레퍼런스

| 스크립트 | 용도 |
|---|---|
| `./ci.sh [COURSE...]` | 워크플로 전체를 로컬에서 실행 |
| `./build.sh <src.md> <temp.md> <out.pdf> [loop]` | 챕터 빌드. `loop` 지정 시 1초 주기 재빌드 |
| `./check_and_release.sh <temp.pdf>` | 검증 후 `release/` 로 PDF·PPTX 배포 |
| `./clean.sh` | 모든 과목의 생성물 삭제 |
| `<course>/check_syntax.sh [NN]` | 문법 검사. 인자 없으면 전체 챕터 |
| `<course>/formatter.sh [NN]` | 코드 포매터 적용 |
| `<course>/clean.sh` | 해당 과목의 생성물 삭제 |

C/C++ 의 `formatter.sh` 는 `${HOME}/clang-format/.clang-format-knr` 를 참조하므로, 별도 `clang-format` 저장소가 필요합니다(`Dockerfile` 참조).

---

## 9. 환경 구성

### 9-1. Docker (권장)

`Dockerfile` 이 gcc/g++, clang-format-19, Node.js, marp-cli, 한글 폰트, Chrome 을 모두 포함합니다. 구성 방법은 루트 `README.md` 참조.

### 9-2. 로컬 실행 시 필요한 것

| 도구 | 용도 |
|---|---|
| Node.js + `@marp-team/marp-cli` | 슬라이드 변환. `check_and_release.sh` 가 `marp` 를 PATH에서 직접 호출하므로 전역 설치 권장 |
| `@marp-team/marp-core`, `markdown-it-shiki` | `engine.js` 가 저장소 루트에서 로드 (로컬 설치 필요) |
| Chrome / Chromium | marp 의 PDF 렌더링 백엔드 |
| 과목별 컴파일러 | 문법 검사 (C: `gcc`, C++: `g++`) |
| poppler-utils (`pdfinfo`, `pdftoppm`) | `check_and_release.sh` 의 페이지 분석 |
| ImageMagick (`convert`, `identify`) | `check_and_release.sh` 의 내용 영역 측정 |
| 한글 폰트 (Noto CJK 등) | 폰트가 없으면 글자가 깨져 내용 영역 측정이 무의미해짐 |

```bash
npm install -g @marp-team/marp-cli
npm install @marp-team/marp-core markdown-it-shiki
```

---

## 10. CI

`.github/workflows/build.yml` 이 `main` / `dev` 로의 push 및 PR 에서 다음을 수행합니다.

1. 과목 디렉터리 자동 탐색(`*/check_syntax.sh`)
2. 과목별로 병렬 잡 실행
3. 과목 전체 소스 문법 검사
4. 모든 챕터를 `build.sh` → `check_and_release.sh` 순서로 처리
5. 생성된 PDF·PPTX 를 `slides-<course>` 아티팩트로 업로드

**새 과목이나 새 챕터를 추가할 때 워크플로 파일은 수정하지 않아도 됩니다.**
