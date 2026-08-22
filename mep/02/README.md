<!-- _class: lead -->
# 마이크로임베디드프로그래밍

## 라즈베리파이 플랫폼

### [munseong.jeong@daejin.ac.kr](mailto:munseong.jeong@daejin.ac.kr)

---

## 라즈베리파이란 (What Is Raspberry Pi)

![h:280 center](img/00-rpi-board.png)

- 영국 라즈베리파이 재단에서 교육용으로 개발한 **싱글 보드 컴퓨터**(SBC)
- 신용카드 크기의 단일 기판에 CPU, 메모리, 입출력 장치 통합 집적
- 뛰어난 가성비와 풍부한 생태계를 바탕으로 교육 및 프로토타이핑의 업계 표준으로 활용

### 싱글 보드 컴퓨터

- 단일 기판 내에 컴퓨터의 주요 구성 요소가 모두 집약된 형태
- 일반 PC와 동일한 **범용 운영체제**(Linux) 구동 가능
- **GPIO 핀**을 탑재하여 MCU처럼 하드웨어를 직접 제어 가능

---

## 라즈베리파이의 특징 (Characteristics)

| 항목 | 내용 |
| --- | --- |
| 프로세서 | ARM 기반 SoC(예: BCM2711, Cortex-A72) |
| 아키텍처 | `aarch64` (`arm64`, 64-bit) |
| 메모리 | 모델별 1GB ~ 8GB LPDDR4 |
| 저장장치 | MicroSD 카드(또는 USB 부팅) |
| 네트워크 | 유선 이더넷, 무선 Wi-Fi, 블루투스 |
| 확장성 | 40핀 GPIO 헤더, USB, HDMI, CSI, DSI |
| 전원 | USB-C 또는 Micro-USB(5V) |

---

## 라즈베리파이 제품 계보 (Model Lineage)

![h:240 center](img/01-rpi-models.png)

| 계열 | 특징 | 주요 용도 |
| --- | --- | --- |
| Model B(3/4/5) | 표준 규격, 다수의 이더넷·USB 포트 탑재 | 데스크톱 대체, 서버, 본 실습 |
| Model A | Model B 대비 이더넷·USB 축소, 저전력 설계 | 임베디드 시스템 내장 |
| Zero / Zero 2 W | 초소형, 저전력, 무선 네트워크 내장 | 소형 IoT, 웨어러블 기기 |
| Compute Module(CM) | 커넥터 방식 모듈(별도 캐리어 보드 필요) | 양산형 제품 내장 |
| Pico | RP2040 MCU 기반(Linux 미탑재) | 베어메탈 하드웨어 제어 |

> **참고:** GPIO 40핀 헤더의 **핀 배치는 세대 간 호환**되므로 동일한 실습 회로 재사용 가능
> **주의:** Pico는 라즈베리파이 브랜드 제품이나 Linux가 구동되지 않는 **MCU** 형태임.

---

## GPIO 헤더 (GPIO Header)

### 핀 번호 체계

![h:300 center](img/02-gpio-pinout.png)

| 체계 | 설명 | 사용 목적 |
| --- | --- | --- |
| 물리 핀 번호 | 헤더의 물리적 위치(1~40번) | 회로 실물 연결 시 적용 |
| BCM 번호 | SoC 내부의 GPIO 제어 번호 | **소프트웨어 제어 시 사용** |

> **주의:** 두 체계를 혼동할 경우 오작동이 발생할 수 있음(본 강의의 모든 소스 코드는 **BCM 번호** 기준 작성)

---

## GPIO의 대체 기능 (Alternate Functions)

- 각 핀은 일반 입출력(GPIO) 외에 **통신 전용 특수 기능**을 겸함

| 기능 | 주요 용도 |
| --- | --- |
| I2C(SDA/SCL) | 2선식 다중 기기 통신 |
| SPI(MOSI/MISO/SCLK/CE) | 고속 동기식 통신 |
| UART(TXD/RXD) | 직렬 통신, 시리얼 콘솔 |
| PWM | 아날로그 형태 신호 출력 |

### 주요 주의사항

- 특수 기능으로 할당된 핀을 일반 GPIO로 사용할 경우 해당 통신 기능 사용 불가
- SPI 및 I2C 인터페이스는 `raspi-config`에서 **명시적으로 활성화**해야 동작
- 핀 배정 전 필요한 통신 인터페이스 규격을 사전 정의할 것

---

## 전기적 주의사항 (Electrical Cautions)

- GPIO는 **3.3V 로직 레벨**을 사용하며, 5V 신호 직접 인가 시 SoC 파손 위험 발생
- 핀당 허용 전류는 최대 약 16mA, 전체 핀 합계는 약 50mA 이내로 제한
- LED 연결 시 반드시 **전류 제한 저항을 직렬로 배치**해야 함

### 저항값 계산 예

- **전원 전압($V_{\text{CC}}$):** **3.3V**(라즈베리파이 GPIO 로직 전압)
- **LED 순방향 전압($V_f$):** 약 **2.0V** *(일반 지시등용 적색·초록색 LED 구동 시 전압 강하량)*
- **목표 전류($I_f$):** 약 **4mA** *(핀당 최대 제한치 16mA 대비 SoC 안정성 확보 및 시인성 타협선)*

$$R = \frac{V_{\text{CC}} - V_f}{I_f} = \frac{3.3 - 2.0}{0.004} = 325\,\Omega \approx 330\,\Omega$$

- **330Ω 저항 선정 이유:** GPIO 과부하를 방지하고 적절한 시인성을 확보하는 최적 수치로 실습 키트에 채택됨
- 모터 등 대전류 부하 연결 시 **트랜지스터 또는 드라이버 회로**를 경유하여 구동

---

## 전원 공급 (Power Supply)

![h:280 center](img/03-power-supply.png)

- 라즈베리파이는 **전원 공급의 안정성 및 품질에 민감함**

| 증상 | 주요 원인 |
| --- | --- |
| 부팅 중 중단 또는 재부팅 | 공급 전류 부족 |
| 화면 내 경고 또는 번개 아이콘 표시 | 저전압 상태 감지 |
| USB 장치 인식 불가 또는 오작동 | 전원 공급 용량 부족 |
| SD 카드 파일 시스템 손상 반복 | 부적절한 전원 강제 차단 |

---

## 전원 공급 (Power Supply) (Cont'd)

### 권장 사항

![h:280 center](img/04-power-supply.png)

- **정격 출력 규격을 준수하는(혹은 그에 준하는) 전용 어댑터 사용 권장**
  - PC USB 포트는 전류 용량이 미흡할 수 있음
- 저전압 상태 모니터링 명령어

```bash
vcgencmd get_throttled     # 0x0 means no throttling
dmesg | grep -i voltage
```

---

## 라즈베리파이의 활용 사례 (Use Cases)

- **홈 서버**: 네트워크 파일 서버, 미디어 스트리밍, DNS 기반 광고 차단
- **IoT 게이트웨이**: 센서 데이터 수집 및 클라우드 플랫폼 전송
- **로보틱스**: 자율주행 및 이동 로봇의 상위 제어 장치
- **엣지 AI**: 실시간 카메라 영상 기반 비전 및 객체 인식 처리
- **산업용 프로토타입**: 양산 전 시스템 개념 검증(PoC)

### 본 교과목에서의 학습 목표

- 라즈베리파이를 활용하여 센서 데이터 수집 → 데이터 처리 → 웹 대시보드 구축 → 서비스 배포까지의 전 과정을 실습함

---

## 라즈베리파이 운영체제 (Raspberry Pi OS)

- 데비안(Debian) 기반의 리눅스 배포판으로, 라즈베리파이 하드웨어 환경에 최적화됨
- 구(舊) 명칭: Raspbian

### 배포판 선택

| 종류 | 주요 특징 | 권장 용도 |
| --- | --- | --- |
| Desktop | GUI 환경 포함 | 일반 학습 및 개발 환경 |
| Lite | CLI 전용(경량화) | 서버 구축 및 임베디드 배포 |
| 64-bit | `arm64` 아키텍처 지원 | **본 강의 실습 기준** |

- 임베디드 운영 환경에서는 불필요한 요소가 제거된 **Lite 버전 사용**을 권장
  - 저장 공간 최적화, 부팅 시간 단축, 보안 공격 표면(Attack Surface) 축소 이점 제공

---

## 부팅 과정 (Boot Process)

![h:190 center](img/05-boot-sequence.png)

1. **SoC ROM**: 전원 인가 시 칩 내부 부트 ROM 실행
2. **부트로더**: SD 카드의 부트 파티션에서 펌웨어 적재
3. **커널 적재**: `kernel8.img` (`arm64` 커널)를 메모리에 적재
4. **디바이스 트리**: `.dtb` 파일을 통해 하드웨어 구성 정보를 커널에 전달
5. **`init` 실행**: 루트 파일 시스템 마운트 후 `systemd` 프로세스 시작
6. **서비스 실행**: 네트워크, SSH 등 주요 시스템 서비스 순차 구동

### 디바이스 트리 (Device Tree)

- 하드웨어 구성 및 주소 할당 정보를 기술하는 데이터 구조
- x86의 BIOS/ACPI와 달리 ARM 아키텍처는 디바이스 트리를 통해 하드웨어 정보를 전달함
- `config.txt` 내 `dtoverlay` 설정을 통해 주변 장치 오버레이 활성화

---

## 부팅 설정 파일 (Boot Configuration)

- 부팅 동작 관련 설정은 `/boot/firmware` 디렉터리의 텍스트 파일로 제어함

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

- 커널에 전달되는 **단일 행**의 부팅 파라미터 지정(루트 파티션, 시리얼 콘솔 등)
- 개행 문자(줄바꿈) 포함 시 부팅 오류가 발생하므로 수정 시 주의 필요

> **참고:** 해당 파일들은 **FAT32 파티션**에 위치하여, 타 PC에 SD 카드를 연결하여 직접 수정 가능함.
> **참고:** 부팅 장애 발생 시 주 복구 수단으로 활용됨.

---

## 파일시스템 구조 (Filesystem Layout)

![h:180 center](img/06-filesystem-tree.png)

| 경로 | 주요 용도 |
| --- | --- |
| `/boot/firmware` | 부트로더, 커널, `config.txt` 위치(FAT32) |
| `/` | 루트 파일 시스템(ext4) |
| `/etc` | 시스템 제어 설정 파일 |
| `/home/<user>` | 사용자 전용 홈 디렉터리 |
| `/dev` | 장치 파일(`gpiochip0`, `video0` 등) |
| `/proc`, `/sys` | 커널 정보를 제공하는 가상 파일 시스템 |
| `/var/log` | 시스템 및 애플리케이션 로그 저장 |

- "모든 것은 파일이다"라는 UNIX 철학에 따라 GPIO 및 주요 장치도 `/dev` 이하 파일 형태로 접근

---

## 장치 파일과 GPIO (Device Files)

- 최신 Raspberry Pi OS는 GPIO를 **문자 디바이스(Character Device)** 형태로 노출
- 예: `/dev/gpiochip0` (GPIO 컨트롤러)
- 레거시 방식인 `/sys/class/gpio` (sysfs) 방식은 더 이상 사용되지 않을 예정(Deprecated)으로 사용 지양

### 문자 디바이스 도입 배경

| 구분 | sysfs(기존) | 문자 디바이스(현재) |
| --- | --- | --- |
| 접근 방식 | 경로 문자열 제어 | `ioctl` 기반 API |
| 소유권 | 명확하지 않음 | 프로세스 단위의 라인 점유 |
| 자원 정리 | 수동 해제 필요 | 프로세스 종료 시 자동 정리 |
| 처리 성능 | 상대적으로 느림 | 우수함(고속 처리) |

- 본 실습에서는 문자 디바이스 API를 추상화한 `libgpiod` 라이브러리를 표준으로 사용함

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
gpioinfo -c gpiochip0    # per-line state and owning process

# Service management
systemctl status ssh
sudo systemctl enable --now ssh
```

---

## 안전한 종료와 SD 카드 (Shutdown and SD Card)

- 전원 무단 차단 시 파일 시스템 손상 및 데이터 손실 위험 발생

```bash
sudo shutdown -h now     # Safely stop processes, unmount FS, and power off
sudo reboot              # Safely stop processes, unmount FS, and restart
```

### SD 카드 수명 관리

- SD 카드는 플래시 메모리 특성상 쓰기 횟수 제한이 존재하므로 과도한 로그 기록 시 수명 단축
- 상용 제품 구현 시 고려사항:
  - 로그 기록 위치를 램 기반 파일 시스템(`tmpfs`)으로 전환
  - 루트 파일 시스템을 읽기 전용(Read-Only)으로 마운트
  - 주요 데이터는 외부 저장 매체 또는 원격 서버로 전송 관리

---

## 서비스 관리 (systemd)

- 리눅스 시스템 서비스는 `systemd`가 관장하며, 임베디드 소프트웨어 배포의 핵심 수단임

```bash
systemctl status ssh             # show status
sudo systemctl start ssh         # start now
sudo systemctl enable ssh        # start automatically on boot
sudo systemctl enable --now ssh  # start and enable in one step

journalctl -u ssh -f                    # follow the log
journalctl -u ssh --since "10 min ago"  # time ranges
```

### systemd 도입의 주요 이점

- 개발한 애플리케이션을 서비스로 등록 시 제공되는 기능:
- 시스템 부팅 시 자동 실행 설정
- 프로세스 비정상 종료 시 자동 재시작
- 통합 로그 관리 시스템(`journalctl`)을 통한 로깅 일원화

---

## 초기 설정 (Initial Setup)

- OS 이미지는 공식 툴인 [**Raspberry Pi Imager**](https://www.raspberrypi.com/software/)를 활용하여 SD 카드에 플래싱
- 플래싱 시 [사전 설정(Advanced Options) 구성](https://www.raspberrypi.com/documentation/computers/getting-started.html#customisation)을 통해 모니터 없는 헤드리스 환경 구축 가능:
  - 호스트명 및 사용자 계정/비밀번호 설정
  - Wi-Fi SSID 및 접속 정보 설정
  - SSH 원격 접속 활성화

### 헤드리스 (Headless) 운용

- 디스플레이 및 입력 장치 없이 네트워크를 통해 원격 제어하는 운용 방식
- 대부분의 임베디드 운영 환경에서 표준으로 채택됨

```bash
ssh <user>@raspberrypi.local  # connect via mDNS(Multicast DNS)
ssh <user>@192.168.0.10       # connect by IP
```

---

## 네트워크 구성 (Network Configuration)

- 최신 Raspberry Pi OS는 **NetworkManager**를 통해 네트워크 제어 수행

```bash
# Scan for and join a wireless network
nmcli device wifi list
sudo nmcli device wifi connect "<SSID>" password "<PASSWORD>"

# Check connection state
nmcli connection show
ip addr show wlan0

# Configure a static IP
# Note: Replace <NAME> with the Connection Profile name
# (NAME column in 'nmcli connection show')
sudo nmcli connection modify "<NAME>" \
  ipv4.addresses 192.168.0.10/24 \
  ipv4.gateway 192.168.0.1 \
  ipv4.dns 8.8.8.8 \
  ipv4.method manual
```

- IP 할당이 변동되는 실습 환경에서는 **고정 IP 설정** 또는 mDNS 활용 권장

---

## 블루투스 (Bluetooth)

### 블루투스 규격의 진화 (Classic vs BLE)

- Bluetooth Classic(1.0~3.0): 대용량 데이터 및 고음질 오디오 스트리밍에 최적화
  - 상시 연결, 높은 전력 소모
- **BLE(Bluetooth Low Energy, 4.0 이상)**: 소량 센서 데이터의 주기적 전송 및 저전력 동작에 최적화
  - 동전 배터리로 수개월~수년 구동

### 라즈베리파이 무선 칩셋 특성 (Dual Mode)

- 라즈베리파이는 Wi-Fi와 블루투스(Classic + BLE) 제어를 단일 칩셋에서 처리함
- 동시 사용 시 동일 2.4GHz 대역 간섭으로 인해 무선 성능 저하가 발생할 수 있음
- 시분할(TDM) 제어로 Classic 오디오 연결 상태에서도 BLE 센서 데이터 수집 가능

![h:160 center](img/07-interference.png)

---

## 블루투스 (Bluetooth) (Cont'd)

### 무선 통신 규격 비교

| 규격 | 통신 거리 | 전력 소모 | 주요 용도 |
| --- | --- | --- | --- |
| Wi-Fi | 중거리 | 높음 | 대용량 데이터 전송, 인터넷 연동 |
| Bluetooth | 단거리 | 중간 | 근거리 대역 기기 연동 |
| BLE | 단거리 | 매우 낮음 | 소형 센서 노드, 배터리 구동 기기 |

### 리눅스 환경의 블루투스 제어 (`bluetoothctl`)

- 라즈베리파이에서 무선 기기 검색, 페어링, 연결을 통합 관리하는 CLI 도구

```bash
bluetoothctl
# [bluetooth]# power on
# [bluetooth]# scan on
# [bluetooth]# pair <MAC>
# [bluetooth]# connect <MAC>
```

---

## 원격 개발 환경 (Remote Development)

- 라즈베리파이 자체 편집 대신 **호스트 PC에서 개발 후 타깃 보드 원격 실행** 방식 권장

### 방식 1: SSH 기반 원격 개발 (Remote Development)

- VS Code의 Remote-SSH 확장을 통한 타깃 보드 내 소스 코드 직접 편집
- 소스 편집은 호스트 PC에서, 빌드 및 실행은 타깃 보드에서 수행

### 방식 2: 크로스 컴파일 (Cross Compilation)

- 호스트 PC에서 타깃용 아키텍처로 빌드를 완료한 후 Executable 바이너리 전송

```bash
scp build/app <user>@<host>:/home/<user>/
ssh <user>@<host>
```

- 대규모 프로젝트일수록 호스트 자원을 활용한 크로스 컴파일의 효율성 증가

---

## 개발 환경 점검 (Environment Check)

```bash
# Compilers
g++ --version            # confirm C++14 support

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

- 장치 접근 권한 미부여 시 I/O 에러가 발생하므로, 환경 구축 후 우선 점검 필요
