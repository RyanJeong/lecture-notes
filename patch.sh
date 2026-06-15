#!/bin/bash

# ============================================================================
# patch.sh
# ============================================================================
# Usage:
#   ./patch.sh
#
# Description:
#   Installs and updates Ubuntu 22.04 dependencies for lecture-notes.
#   Includes Java, Maven, Node.js, JPlag (with report viewer), and tools.
# ============================================================================

set -Eeuo pipefail

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

on_error() {
  local exit_code="$?"
  error "Failed at line ${BASH_LINENO[0]}: ${BASH_COMMAND} (exit ${exit_code})"
  exit "$exit_code"
}

append_once_to_bashrc() {
  local line="$1"
  if grep -Fqx "$line" "$HOME/.bashrc"; then
    info "bashrc already contains: $line"
  else
    printf '%s\n' "$line" >>"$HOME/.bashrc"
    info "Added to bashrc: $line"
  fi
}

# Extract the FEATURE Java version (e.g. 25 from "javac 25.0.3", 21 from
# 'openjdk version "21.0.7"') from a java/javac binary. Returns "" on failure.
java_major_of() {
  # $1: path to a java or javac binary
  local v
  # Grab the first dotted-number token (e.g. 25.0.3, 21.0.7, 25), then keep
  # only the part before the first dot. `|| true` keeps set -e happy if the
  # binary prints nothing parseable.
  v="$("$1" -version 2>&1 | head -n1 | grep -oE '[0-9]+(\.[0-9]+)*' | head -n1 || true)"
  printf '%s' "${v%%.*}"
}

trap on_error ERR

# Active sudo and snap (chrome dependency)
sudo apt update
sudo apt upgrade -y
sudo apt install -y snapd curl git wget apt-transport-https gnupg

JAVA_VERSION_REQUIRED=25
info "1. Install Java ${JAVA_VERSION_REQUIRED} (required by JPlag 6.x)"

# --- 1a. Detect the current default JDK -------------------------------------
java_version=0
if command -v javac >/dev/null 2>&1; then
  detected="$(java_major_of "$(command -v javac)")"
  [ -n "$detected" ] && java_version="$detected"
fi

# --- 1b. Install Temurin 25 if no JDK >= required is present ----------------
if [ "$java_version" -lt "$JAVA_VERSION_REQUIRED" ]; then
  info "No JDK >= ${JAVA_VERSION_REQUIRED} found (detected: ${java_version}). Installing Temurin ${JAVA_VERSION_REQUIRED} ..."
  wget -O - https://packages.adoptium.net/artifactory/api/gpg/key/public |
    sudo gpg --dearmor --yes -o /usr/share/keyrings/adoptium.gpg
  echo "deb [signed-by=/usr/share/keyrings/adoptium.gpg] https://packages.adoptium.net/artifactory/deb jammy main" |
    sudo tee /etc/apt/sources.list.d/adoptium.list >/dev/null
  sudo apt update
  sudo apt install -y "temurin-${JAVA_VERSION_REQUIRED}-jdk"
else
  info "JDK ${java_version} (>= ${JAVA_VERSION_REQUIRED}) already present. Skipping install ..."
fi

# --- 1c. Resolve a JAVA_HOME whose javac major version is >= required --------
# Prefer the exact Temurin build, then fall back to the highest JDK available.
resolve_java_home() {
  local want="$1" home major best="" best_major=0
  shopt -s nullglob
  for home in /usr/lib/jvm/temurin-"${want}"-jdk* /usr/lib/jvm/*; do
    [ -x "$home/bin/javac" ] || continue
    major="$(java_major_of "$home/bin/javac")"
    [ -n "$major" ] || continue
    if [ "$major" -ge "$want" ] && [ "$major" -gt "$best_major" ]; then
      best="$home"
      best_major="$major"
    fi
  done
  shopt -u nullglob
  printf '%s' "$best"
}

JAVA_HOME="$(resolve_java_home "$JAVA_VERSION_REQUIRED")"
if [ -z "$JAVA_HOME" ]; then
  error "No JDK with javac >= ${JAVA_VERSION_REQUIRED} found under /usr/lib/jvm."
  error "JPlag 6.x requires Java SE ${JAVA_VERSION_REQUIRED}. Aborting before the build."
  exit 1
fi
export JAVA_HOME
export PATH="$JAVA_HOME/bin:$PATH"

# --- 1d. Make this JDK the system default so every tool (incl. mvn) uses it -
sudo update-alternatives --install /usr/bin/java java "$JAVA_HOME/bin/java" 2000
sudo update-alternatives --install /usr/bin/javac javac "$JAVA_HOME/bin/javac" 2000
sudo update-alternatives --set java "$JAVA_HOME/bin/java"
sudo update-alternatives --set javac "$JAVA_HOME/bin/javac"

# --- 1e. Persist for future shells / manual re-runs -------------------------
append_once_to_bashrc "export JAVA_HOME=$JAVA_HOME"
append_once_to_bashrc 'export PATH=$JAVA_HOME/bin:$PATH'

info "Using JAVA_HOME=$JAVA_HOME"
info "java  -> $(java -version 2>&1 | head -n1)"
info "javac -> $(javac -version 2>&1 | head -n1)"

MAVEN_VERSION_REQUIRED=3.9.11
info "2. Install Maven ${MAVEN_VERSION_REQUIRED}"

maven_version=0.0.0
if command -v mvn >/dev/null 2>&1; then
  maven_version_str=$(mvn --version 2>/dev/null | head -n 1) &&
    maven_version=$(echo "$maven_version_str" | awk '{print $3}')
fi

if [ "$(printf '%s\n' "$MAVEN_VERSION_REQUIRED" "$maven_version" | sort -V | tail -n1)" = "$maven_version" ]; then
  info "Maven has already installed. Skipping ..."
else
  maven_tgz="apache-maven-${MAVEN_VERSION_REQUIRED}-bin.tar.gz"
  sudo apt remove --purge maven -y || true
  wget "https://archive.apache.org/dist/maven/maven-3/${MAVEN_VERSION_REQUIRED}/binaries/${maven_tgz}"
  tar -xzf "${maven_tgz}"
  rm -f "${maven_tgz}"
  sudo rm -rf /opt/maven
  sudo mv "apache-maven-${MAVEN_VERSION_REQUIRED}" /opt/maven
  export M2_HOME=/opt/maven
  export PATH="$M2_HOME/bin:$PATH"
  append_once_to_bashrc 'export M2_HOME=/opt/maven'
  append_once_to_bashrc 'export PATH=$M2_HOME/bin:$PATH'
fi

NODE_VERSION_REQUIRED=22
info "3. Install Node.js ${NODE_VERSION_REQUIRED}"

node_version=0
if command -v node >/dev/null 2>&1; then
  node_version=$(node --version 2>/dev/null | sed 's/^v//' | cut -d. -f1)
fi

if [ "$node_version" -ge "$NODE_VERSION_REQUIRED" ]; then
  info "Node.js has already installed. Skipping ..."
else
  sudo apt remove -y nodejs npm || true
  curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash -
  sudo apt install -y nodejs
fi

info "4. Install JPlag"

if compgen -G "$HOME/jplag/cli/target/jplag-*-jar-with-dependencies.jar" >/dev/null; then
  info "JPlag has already installed. Skipping ..."
else
  if [ -d "$HOME/jplag/.git" ]; then
    info "Existing jplag repository found. Pull latest changes ..."
    git -C "$HOME/jplag" pull --ff-only
  else
    rm -rf "$HOME/jplag"
    git clone https://github.com/jplag/jplag.git "$HOME/jplag"
  fi

  # Hard sanity check: the build MUST run on JDK >= required, or javac will
  # reject the "invalid target release: 25" and the whole reactor fails.
  build_java_major="$(java_major_of "$JAVA_HOME/bin/javac")"
  if [ -z "$build_java_major" ] || [ "$build_java_major" -lt "$JAVA_VERSION_REQUIRED" ]; then
    error "javac major is '${build_java_major}', but JPlag requires >= ${JAVA_VERSION_REQUIRED}."
    error "Refusing to build with the wrong JDK (would fail: invalid target release)."
    exit 1
  fi

  pushd "$HOME/jplag" >/dev/null
  # Pin JAVA_HOME explicitly for the Maven invocation so there is no ambiguity
  # about which javac the compiler plugin uses.
  JAVA_HOME="$JAVA_HOME" PATH="$JAVA_HOME/bin:$PATH" \
    mvn -P with-report-viewer clean package assembly:single \
    -pl cli,core,language-api,language-antlr-utils,languages/c,languages/cpp \
    -am \
    -DskipTests
  jplag_jar="$(compgen -G "$HOME/jplag/cli/target/jplag-*-jar-with-dependencies.jar" | head -n 1 || true)"
  [ -n "$jplag_jar" ]
  java -jar "$jplag_jar" --help >/dev/null 2>&1
  popd >/dev/null
fi

info "5. Install Marp"

if command -v marp >/dev/null 2>&1; then
  info "marp has already installed. Skipping ..."
else
  sudo npm install -g npm
  sudo npm install -g @marp-team/marp-cli
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
  sudo apt install -y locales
  if ! grep -qE '^\s*en_US\.UTF-8\s+UTF-8\b' /etc/locale.gen; then
    echo 'en_US.UTF-8 UTF-8' | sudo tee -a /etc/locale.gen >/dev/null
  fi
  sudo locale-gen
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

info "9. install pdfinfo (poppler-utils) and imagemagick"

sudo apt install -y poppler-utils imagemagick

info "(Opt.) Install VSCode extensions"

# Note: make IDs in lowercase
EXTENSIONS=(
  "davidanson.vscode-markdownlint"
  "dzylikecode.md-paste-enhanced"
  "emeraldwalk.runonsave"
  "mathematic.vscode-pdf"
)

for EXT in "${EXTENSIONS[@]}"; do
  if ! code --list-extensions | grep -q "${EXT}$"; then
    info "Installing VSCode extension: ${EXT}"
    code --install-extension "$EXT"
  else
    info "Extension $EXT is already installed. Skipping ..."
  fi
done

# Clean
sudo apt clean
sudo rm -rf /var/lib/apt/lists/
info "Done."
