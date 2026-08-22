<!-- _class: lead -->
# 마이크로임베디드프로그래밍

## 라즈베리파이 플랫폼

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 라즈베리파이란 (What Is Raspberry Pi)

![h:280 center](img/00-rpi-board.png)

- 영국 라즈베리파이 재단이 교육용으로 개발한 **싱글 보드 컴퓨터**(SBC)
- 신용카드 크기의 기판에 CPU, 메모리, 입출력이 모두 집적
- 저렴한 가격과 방대한 자료 덕분에 교육·프로토타이핑의 사실상 표준

### 싱글 보드 컴퓨터

- 하나의 기판에 컴퓨터의 모든 요소가 포함됨
- 일반 PC와 동일하게 **범용 운영체제**(Linux)를 구동
- 동시에 **GPIO 핀**을 통해 MCU처럼 하드웨어를 직접 제어

---

## 라즈베리파이의 특징 (Characteristics)

| 항목 | 내용 |
| --- | --- |
| 프로세서 | ARM 기반 SoC (예: BCM2711, Cortex-A72) |
| 아키텍처 | `aarch64` (`arm64`, 64-bit) |
| 메모리 | 모델에 따라 1GB ~ 8GB LPDDR4 |
| 저장장치 | MicroSD 카드(또는 USB 부팅) |
| 네트워크 | 유선 이더넷, 무선 WiFi, 블루투스 |
| 확장 | 40핀 GPIO 헤더, USB, HDMI, CSI, DSI |
| 전원 | USB-C 또는 Micro-USB, 5V |

- 본 수업의 타깃 아키텍처는 **`arm64`**

---

## 라즈베리파이 제품 계보 (Model Lineage)

![h:240 center](img/01-rpi-models.png)

| 계열 | 특징 | 용도 |
| --- | --- | --- |
| Model B (3/4/5) | 표준 크기, 이더넷·USB 다수 | 데스크톱 대체, 서버, 본 수업 |
| Model A | B에서 이더넷·USB 축소, 저전력 | 임베디드 내장 |
| Zero / Zero 2 W | 초소형, 저전력, 무선 내장 | 소형 IoT, 웨어러블 |
| Compute Module (CM) | 커넥터 방식 모듈, 캐리어 보드 필요 | **양산 제품 내장** |
| Pico | RP2040 **MCU** — Linux 미탑재 | 베어메탈 제어 |

> GPIO 40핀 헤더의 **핀 배치는 세대 간 호환**되므로 실습 회로는 그대로 사용 가능
> **주의**: Pico는 이름은 라즈베리파이지만 **MCU** 이며 Linux가 동작하지 않음.

---

## GPIO 헤더 (GPIO Header)

### 핀 번호 체계

![h:300 center](img/02-gpio-pinout.png)

| 체계 | 설명 | 사용 |
| --- | --- | --- |
| 물리 핀 번호 | 헤더의 물리적 위치(1~40) | 회로 연결 시 |
| BCM 번호 | SoC 내부의 GPIO 번호 | **소프트웨어에서 사용** |

> 두 체계를 혼동하면 엉뚱한 핀을 제어하게 됨(본 수업의 모든 코드는 **BCM 번호**를 기준으로 작성함)

---

## GPIO의 대체 기능 (Alternate Functions)

- 각 핀은 단순 입출력 외에 **통신용 특수 기능**을 겸함

| 기능 | 용도 | 본 수업에서 |
| --- | --- | --- |
| I2C (SDA/SCL) | 2선식 다중 장치 통신 | 센서 모듈 |
| SPI (MOSI/MISO/SCLK/CE) | 고속 동기 통신 | **MCP3008 ADC**(실습 04) |
| UART (TXD/RXD) | 직렬 통신, 콘솔 | 디버깅 |
| PWM | 아날로그 형태 출력 | LED 밝기, 부저 |

### 주의할 점

- 특수 기능 핀을 일반 GPIO로 쓰면 해당 통신 기능을 사용할 수 없음
- SPI·I2C는 `raspi-config`에서 **명시적으로 활성화**해야 동작
- 핀을 배정하기 전에 어떤 통신을 쓸지 먼저 결정할 것

---

## 전기적 주의사항 (Electrical Cautions)

- GPIO는 **3.3V 로직** — 5V 신호를 직접 인가하면 SoC가 손상됨
- 핀당 최대 전류는 약 16mA, 전체 합계는 약 50mA로 제한
- LED는 반드시 **전류 제한 저항과 직렬** 연결

### 저항값 계산 예 (설계 수치 채택 이유)

- **전원 전압 ($V_{\text{CC}}$):** **3.3V** (라즈베리파이 GPIO 로직 전압)
- **LED 순방향 전압 ($V_f$):** 약 **2.0V** *(일반 지시등용 적색·초록색 LED의 구동 전압 강하량)*
- **목표 전류 ($I_f$):** 약 **4mA** *(핀당 제한 16mA 대비 SoC 안정성 확보 및 적정 밝기 타협선)*

$$R = \frac{V_{\text{CC}} - V_f}{I_f} = \frac{3.3 - 2.0}{0.004} = 325\,\Omega \approx 330\,\Omega$$

- **330Ω 저항의 의미:** GPIO 과부하를 막고 눈부심 없이 실습하기 가장 적절하여 실습 키트에 포함됨
- 모터처럼 전류가 큰 부하는 **트랜지스터나 드라이버 회로**를 거쳐 구동

---

## 전원 공급 (Power Supply)

![h:280 center](img/03-power-supply.png)

- 라즈베리파이는 **전원 품질에 민감**한 보드

| 증상 | 흔한 원인 |
| --- | --- |
| 부팅 도중 멈춤·재시작 | 전류 부족 |
| 화면에 번개 아이콘 표시 | 저전압 감지 |
| USB 장치 인식 실패 | 전류 여유 부족 |
| SD 카드 손상 반복 | 갑작스러운 전원 차단 |

---

## 전원 공급 (Power Supply) (Cont'd)

### 권장 사항

![h:310 center](img/04-power-supply.png)

- **정격 전류를 충족하는 정품 어댑터** 사용 — PC의 USB 포트로는 부족한 경우가 많음
- 저전압 여부 확인

```bash
vcgencmd get_throttled     # 0x0 means no throttling
dmesg | grep -i voltage
```

---

## 라즈베리파이의 활용 사례 (Use Cases)

- **홈 서버**: 파일 서버, 미디어 서버, 광고 차단 DNS
- **IoT 게이트웨이**: 센서 데이터 수집과 클라우드 전송
- **로보틱스**: 이동 로봇의 상위 제어기
- **엣지 AI**: 카메라 영상에서 객체를 직접 탐지
- **산업 프로토타이핑**: 양산 전 개념 검증(PoC)

> 본 강의에서는 라즈베리파이를 활용해 센서 → 처리 → 웹 대시보드 → 배포까지 전 과정을 경험

---

## 라즈베리파이 운영체제 (Raspberry Pi OS)

- 데비안(Debian) 기반의 리눅스 배포판이며, 라즈베리파이에 최적화됨
- 과거 명칭은 Raspbian

### 배포판 선택

| 종류 | 특징 | 용도 |
| --- | --- | --- |
| Desktop | GUI 포함 | 학습, 개발 |
| Lite | CLI 전용, 경량 | 서버, 임베디드 배포 |
| 64-bit | arm64 | **본 수업 기준** |

- 임베디드 배포에서는 불필요한 구성요소가 없는 **Lite**를 선호
- 저장 공간, 부팅 시간, 공격 표면이 모두 줄어듦

---

## 부팅 과정 (Boot Process)

![h:190 center](img/05-boot-sequence.png)

1. **SoC ROM**: 전원 인가 시 칩 내부의 부트 ROM이 실행됨
2. **부트로더**: SD 카드의 부트 파티션에서 펌웨어를 적재
3. **커널 적재**: `kernel8.img`(`arm64` 커널)를 메모리에 적재
4. **디바이스 트리**: `.dtb` 파일로 하드웨어 구성을 커널에 전달
5. **`init` 실행**: 루트 파일시스템을 마운트하고 `systemd` 시작
6. **서비스 시작**: 네트워크, SSH 등 각 서비스가 순차적으로 기동

### 디바이스 트리 (Device Tree)

- 어떤 하드웨어가 어느 주소에 붙어 있는지 기술한 자료 구조
- x86의 BIOS/ACPI와 달리, ARM은 디바이스 트리로 하드웨어를 설명
- `config.txt`의 `dtoverlay` 설정으로 주변장치를 활성화

---

## 부팅 설정 파일 (Boot Configuration)

- 부팅 동작은 `/boot/firmware`의 텍스트 파일로 제어

### `config.txt`

```ini
# Enable peripherals
dtparam=i2c_arm=on
dtparam=spi=on

# Add features via overlays
dtoverlay=disable-bt          # free the UART by disabling Bluetooth

# Force HDMI when no display is detected
hdmi_force_hotplug=1
```

### `cmdline.txt`

- 커널에 전달되는 **한 줄짜리** 부팅 인자(루트 파티션, 콘솔 등)
- 줄바꿈을 넣으면 부팅에 실패하므로 편집 시 주의

> 두 파일은 **FAT32 파티션**에 있어 다른 PC에서도 SD 카드를 꽂아 수정 가능.
> 부팅이 안 될 때 복구하는 주요 수단

---

## 파일시스템 구조 (Filesystem Layout)

![h:180 center](img/06-filesystem-tree.png)

| 경로 | 용도 |
| --- | --- |
| `/boot/firmware` | 부트로더, 커널, `config.txt` (FAT32) |
| `/` | 루트 파일시스템 (ext4) |
| `/etc` | 시스템 설정 파일 |
| `/home/<user>` | 사용자 홈 디렉터리 |
| `/dev` | 장치 파일 — `gpiochip0`, `video0` 등 |
| `/proc`, `/sys` | 커널이 제공하는 가상 파일시스템 |
| `/var/log` | 로그 |

- **모든 것이 파일**이라는 UNIX 철학에 따라, GPIO와 기타 장치도 `/dev`의 파일로 접근

---

## 장치 파일과 GPIO (Device Files)

- 현행 Raspberry Pi OS는 GPIO를 **문자 디바이스**로 노출
  - `/dev/gpiochip0` — GPIO 컨트롤러
- 과거의 `/sys/class/gpio` (sysfs) 방식은 폐기 예정이므로 사용하지 않음

### 왜 문자 디바이스인가

| 항목 | sysfs (구) | 문자 디바이스 (현) |
| --- | --- | --- |
| 접근 방식 | 경로 문자열 조작 | `ioctl` 기반 API |
| 소유권 | 불명확 | 프로세스가 라인을 점유 |
| 종료 시 정리 | 수동 | 프로세스 종료 시 자동 해제 |
| 성능 | 느림 | 빠름 |

- 본 수업은 문자 디바이스를 감싼 **libgpiod** 라이브러리를 사용

---

## 기본 운용 명령어 (Basic Operations)

```bash
# System information
uname -a                 # kernel version and architecture (expect aarch64)
cat /etc/os-release      # distribution details
vcgencmd measure_temp    # SoC temperature

# Package management
sudo apt update && sudo apt upgrade
sudo apt install -y libgpiod-dev gpiod

# GPIO inspection
gpiodetect               # list controllers
gpioinfo gpiochip0       # per-line state and owning process

# Service management
systemctl status ssh
sudo systemctl enable --now ssh
```

---

## 안전한 종료와 SD 카드 (Shutdown and SD Card)

- 전원을 그냥 뽑으면 파일시스템이 손상될 수 있음

```bash
sudo shutdown -h now     # clean shutdown
sudo reboot              # restart
```

### SD 카드 수명 관리

- SD 카드는 쓰기 횟수에 한계가 있어, 로그를 과도하게 기록하면 수명이 단축됨
- 완성된 제품에서는 다음을 고려
  - 로그를 메모리 파일시스템(`tmpfs`)에 기록
  - 루트 파일시스템을 읽기 전용으로 마운트
  - 중요한 데이터는 외부 저장소나 서버로 전송

---

## 서비스 관리 (systemd)

- Linux의 서비스는 `systemd`가 관리하며, 임베디드 배포의 핵심 수단

```bash
systemctl status ssh          # show status
sudo systemctl start ssh      # start now
sudo systemctl enable ssh     # start automatically on boot
sudo systemctl enable --now ssh   # enable and start in one step

journalctl -u ssh -f          # follow the log
journalctl -u ssh --since "10 min ago"
```

### 왜 중요한가

- 내가 만든 프로그램도 서비스로 등록하면
  - 부팅과 동시에 자동 실행
  - 비정상 종료 시 자동 재시작
  - 로그가 `journalctl`로 일원화됨
- 8장의 배포 파이프라인에서 이 방식을 그대로 사용

---

## 초기 설정 (Initial Setup)

- OS 이미지는 **Raspberry Pi Imager**로 SD 카드에 기록
- 기록 시 고급 설정에서 다음을 미리 지정하면 모니터 없이 부팅 가능
  - 호스트명, 사용자 계정과 비밀번호
  - WiFi SSID와 비밀번호
  - SSH 활성화

### 헤드리스 (Headless) 운용

- 모니터·키보드 없이 네트워크로만 접속하는 방식
- 임베디드 장치는 대부분 헤드리스로 운용됨

```bash
ssh <user>@<hostname>.local     # connect via mDNS
ssh <user>@192.168.0.10         # connect by IP
```

---

## 네트워크 구성 (Network Configuration)

- 현행 Raspberry Pi OS는 **NetworkManager**로 네트워크를 관리

```bash
# Scan for and join a wireless network
nmcli device wifi list
sudo nmcli device wifi connect "<SSID>" password "<PASSWORD>"

# Check connection state
nmcli connection show
ip addr show wlan0

# Configure a static IP
sudo nmcli connection modify "<NAME>" \
  ipv4.addresses 192.168.0.10/24 \
  ipv4.gateway 192.168.0.1 \
  ipv4.dns 8.8.8.8 \
  ipv4.method manual
```

- 실습실처럼 IP가 바뀌는 환경에서는 **고정 IP** 또는 mDNS가 유용

---

## 블루투스 (Bluetooth)

```bash
bluetoothctl
# [bluetooth]# power on
# [bluetooth]# scan on
# [bluetooth]# pair <MAC>
# [bluetooth]# connect <MAC>
```

- 라즈베리파이는 WiFi와 블루투스를 하나의 칩에서 처리
- 두 기능을 동시에 사용하면 대역 간섭으로 성능이 저하될 수 있음

### 무선 통신의 선택 기준

| 방식 | 거리 | 전력 | 용도 |
| --- | --- | --- | --- |
| WiFi | 중 | 높음 | 대용량 데이터, 인터넷 연결 |
| Bluetooth | 짧음 | 낮음 | 근거리 기기 연동 |
| BLE | 짧음 | 매우 낮음 | 센서 비콘, 배터리 장치 |

---

## 원격 개발 환경 (Remote Development)

- 라즈베리파이에서 직접 편집하는 대신, **호스트 PC에서 편집하고 원격 실행**

### 방법 1: SSH + 원격 편집

- VS Code의 Remote-SSH 확장으로 라즈베리파이의 파일을 직접 편집
- 편집은 호스트에서, 빌드와 실행은 타깃에서 수행

### 방법 2: 크로스 컴파일 (6주차)

- 호스트에서 빌드까지 마치고, 결과 바이너리만 전송

```bash
scp build/app <user>@<host>:/home/<user>/
ssh <user>@<host> ./app
```

- 빌드가 오래 걸릴수록 크로스 컴파일의 이점이 커짐

---

## 개발 환경 점검 (Environment Check)

```bash
# Compilers
g++ --version            # confirm C++14 support
cmake --version

# GPIO library
pkg-config --modversion libgpiod
gpiodetect

# Camera and audio
v4l2-ctl --list-devices  # confirm the webcam is detected
arecord -l               # confirm the microphone is detected
```

### 권한 설정

```bash
# Grant GPIO, video and audio access (takes effect after re-login)
sudo usermod -aG gpio,video,audio "$USER"
```

- 권한이 없으면 장치 열기에서 실패하므로, 오류 발생 시 가장 먼저 확인할 것
