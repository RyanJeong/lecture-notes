#!/bin/bash

set -euo pipefail

# Color functions (using printf)
color_red() { printf "\033[31m%s\033[0m" "$1"; }
color_green() { printf "\033[32m%s\033[0m" "$1"; }
color_yellow() { printf "\033[33m%s\033[0m" "$1"; }
color_blue() { printf "\033[34m%s\033[0m" "$1"; }
color_magenta() { printf "\033[35m%s\033[0m" "$1"; }
color_cyan() { printf "\033[36m%s\033[0m" "$1"; }
color_bold() { printf "\033[1m%s\033[0m" "$1"; }

# Logging functions
info() { printf "%s %s\n" "$(color_green "[$(basename "$0")][INFO]")" "$1"; }
warn() { printf "%s %s\n" "$(color_yellow "[$(basename "$0")][WARN]")" "$1"; }
error() { printf "%s %s\n" "$(color_red "[$(basename "$0")][ERROR]")" "$1"; }
debug() { printf "%s %s\n" "$(color_cyan "[$(basename "$0")][DEBUG]")" "$1"; }

# Active sudo and snap (chrome dependency)
sudo apt update && sudo apt upgrade -y && sudo apt install -y snapd

JAVA_VERSION_REQUIRED=21
info "1. Install Java ${JAVA_VERSION_REQUIRED}"

java_version=0
if command -v java --version $ >/dev/null; then
  java_version_str=$(java --version 2>/dev/null | head -n 1) &&
    java_version=$(echo "$java_version_str" | awk '{print $2}' | cut -d. -f1)
fi

if [ "$java_version" -ge 21 ]; then
  info "Java has already installed. Skipping ..."
else
  sudo apt update &&
    sudo apt install -y wget apt-transport-https gnupg &&
    wget -O - https://packages.adoptium.net/artifactory/api/gpg/key/public | sudo gpg --dearmor -o /usr/share/keyrings/adoptium.gpg &&
    echo "deb [signed-by=/usr/share/keyrings/adoptium.gpg] https://packages.adoptium.net/artifactory/deb jammy main" | sudo tee /etc/apt/sources.list.d/adoptium.list &&
    sudo apt update &&
    sudo apt install -y temurin-21-jdk
fi

MAVEN_VERSION_REQUIRED=3.9.11
info "2. Install Maven ${MAVEN_VERSION_REQUIRED}"

maven_version=0.0.0
if command -v mvn --version $ >/dev/null; then
  maven_version_str=$(mvn --version 2>/dev/null | head -n 1) &&
    maven_version=$(echo "$maven_version_str" | awk '{print $3}')
fi

if [ "$(printf '%s\n' "$MAVEN_VERSION_REQUIRED" "$maven_version" | sort -V | tail -n1)" = "$maven_version" ]; then
  info "Maven has already installed. Skipping ..."
else
  sudo apt remove --purge maven -y &&
    wget "https://downloads.apache.org/maven/maven-3/${MAVEN_VERSION_REQUIRED}/binaries/apache-maven-${MAVEN_VERSION_REQUIRED}-bin.tar.gz" &&
    tar -xzf "apache-maven-${MAVEN_VERSION_REQUIRED}-bin.tar.gz" &&
    rm "apache-maven-${MAVEN_VERSION_REQUIRED}-bin.tar.gz" &&
    sudo mv "apache-maven-${MAVEN_VERSION_REQUIRED}" /opt/maven &&
    export M2_HOME=/opt/maven &&
    echo 'export M2_HOME=/opt/maven' >>~/.bashrc &&
    export PATH=$M2_HOME/bin:$PATH &&
    echo 'export PATH=$M2_HOME/bin:$PATH' >>~/.bashrc &&
    source ~/.bashrc
fi

NODE_VERSION_REQUIRED=22
info "3. Install Node.js ${NODE_VERSION_REQUIRED}"

node_version=0
if command -v nodejs --version $ >/dev/null; then
  node_version=$(nodejs --version 2>/dev/null | sed 's/^v//' | cut -d. -f1)
fi

if [ "$node_version" -ge "$NODE_VERSION_REQUIRED" ]; then
  info "Node.js has already installed. Skipping ..."
else
  curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash - &&
    sudo apt install -y nodejs
fi

info "4. Install JPlag"

if [ -f $HOME/jplag/cli/target/jplag-*-jar-with-dependencies.jar ]; then
  info "JPlag has already installed. Skipping ..."
else
  pushd $HOME >/dev/null 2>&1 &&
    git clone https://github.com/jplag/jplag.git &&
    cd jplag &&
    mvn -P with-report-viewer clean package assembly:single \
      -pl cli,core,languages,language-api,language-antlr-utils \
      -am \
      -DskipTests &&
    java -jar $HOME/jplag/cli/target/jplag-*-jar-with-dependencies.jar --help >/dev/null 2>&1 &&
    popd >/dev/null 2>&1
fi

info "5. Install Marp"

if command -v marp $ >/dev/null; then
  info "marp has already installed. Skipping ..."
else
  sudo npm install -g npm &&
    sudo npm install -g @marp-team/marp-cli &&
    npm i --save @marp-team/marp-core markdown-it-shiki
fi

info "6. Install Firefox"

sudo install -d -m 0755 /etc/apt/keyrings
curl -fsSL https://packages.mozilla.org/apt/repo-signing-key.gpg |
  sudo gpg --dearmor --yes -o /etc/apt/keyrings/packages.mozilla.org.gpg

echo "deb [signed-by=/etc/apt/keyrings/packages.mozilla.org.gpg] https://packages.mozilla.org/apt mozilla main" |
  sudo tee /etc/apt/sources.list.d/mozilla.list >/dev/null

sudo tee /etc/apt/preferences.d/mozilla >/dev/null <<'EOF'
Package: firefox*
Pin: origin packages.mozilla.org
Pin-Priority: 1001
EOF

sudo apt update
sudo apt install -y firefox

WANT_LOCALE="en_US.UTF-8"
info "7. Set locale ${WANT_LOCALE}"

if locale -a 2>/dev/null | grep -qiE '^en_US\.utf8$|^en_US\.UTF-8$'; then
  info "Locale has already set. Skipping ..."
else
  sudo apt install -y locales &&
    if ! grep -qE '^\s*en_US\.UTF-8\s+UTF-8\b' /etc/locale.gen; then
      echo 'en_US.UTF-8 UTF-8' | sudo tee -a /etc/locale.gen >/dev/null
    fi &&
    sudo locale-gen &&
    sudo update-locale LANG="${WANT_LOCALE}" LC_ALL="${WANT_LOCALE}"
fi

info "8. Install fonts"

PKGS=(
  fonts-noto
  fonts-noto-cjk
  fonts-noto-cjk-extra
  fonts-nanum
  fonts-unfonts-core
  fonts-unfonts-extra
)

for pkg in "${PKGS[@]}"; do
  if dpkg -s "$pkg" >/dev/null 2>&1; then
    info "${pkg} has already installed. Skipping ..."
  else
    sudo apt install -y "$pkg"
  fi
done

info "(Opt.) Install VSCode extensions"

# Note: make IDs in lowercase
EXTENSIONS=(
  "davidanson.vscode-markdownlint"
  "dzylikecode.md-paste-enhanced"
  "emeraldwalk.runonsave"
  "mathematic.vscode-pdf"
)

for EXT in "${EXTENSIONS[@]}"; do
  if ! code --list-extensions | grep "${EXT}$"; then
    info "Installing VSCode extension: ${EXT}"
    code --install-extension "$EXT"
  else
    info "Extension $EXT is already installed. Skipping ..."
  fi
done

# Clean
sudo apt clean && sudo rm -rf /var/lib/apt/lists/ &&
  info "Done."
