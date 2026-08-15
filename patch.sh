#!/usr/bin/env bash

# ============================================================================
# patch.sh
# ============================================================================
# Usage:
#   ./patch.sh [OPTIONS]
#
# Description:
#   Install and update the Ubuntu 22.04 dependencies for lecture-notes:
#   Java, Maven, Node.js, JPlag (with report viewer), Marp, Firefox, fonts,
#   and the PDF tooling used by check_and_release.sh.
#
#   Every step is idempotent: an already-satisfied dependency is skipped, so
#   the script is safe to re-run.
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./patch.sh
#
# Dependencies:
#   sudo, and a Debian/Ubuntu system with apt-get
#
# ============================================================================

set -euo pipefail
# Inherit the ERR trap into functions so on_error() reports their failures.
set -E

color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly JAVA_VERSION_REQUIRED=25
readonly MAVEN_VERSION_REQUIRED=3.9.11
readonly NODE_VERSION_REQUIRED=22
readonly WANT_LOCALE="en_US.UTF-8"

readonly FONT_PKGS=(
  fonts-noto
  fonts-noto-cjk
  fonts-noto-cjk-extra
  fonts-nanum
  fonts-unfonts-core
  fonts-unfonts-extra
)

# unzip is required by assignment/unzip.sh; poppler-utils and imagemagick by
# check_and_release.sh.
readonly TOOL_PKGS=(
  poppler-utils
  imagemagick
  unzip
)

# Note: make IDs in lowercase; `code --list-extensions` reports them that way.
readonly VSCODE_EXTENSIONS=(
  "davidanson.vscode-markdownlint"
  "dzylikecode.md-paste-enhanced"
  "emeraldwalk.runonsave"
  "mathematic.vscode-pdf"
)

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

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

# Install only the packages that are missing, so re-runs stay quiet and fast.
apt_install_missing() {
  local -a missing=()
  local pkg

  for pkg in "$@"; do
    if dpkg -s "$pkg" >/dev/null 2>&1; then
      info "${pkg} has already installed. Skipping ..."
    else
      missing+=("$pkg")
    fi
  done

  [[ "${#missing[@]}" -eq 0 ]] && return 0
  sudo apt-get install -y "${missing[@]}"
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

install_java() {
  info "1. Install Java ${JAVA_VERSION_REQUIRED} (required by JPlag 6.x)"

  # --- 1a. Detect the current default JDK -----------------------------------
  local java_version=0 detected
  if command -v javac >/dev/null 2>&1; then
    detected="$(java_major_of "$(command -v javac)")"
    [ -n "$detected" ] && java_version="$detected"
  fi

  # --- 1b. Install Temurin if no JDK >= required is present -----------------
  if [ "$java_version" -lt "$JAVA_VERSION_REQUIRED" ]; then
    info "No JDK >= ${JAVA_VERSION_REQUIRED} found (detected: ${java_version}). Installing Temurin ${JAVA_VERSION_REQUIRED} ..."
    wget -O - https://packages.adoptium.net/artifactory/api/gpg/key/public |
      sudo gpg --dearmor --yes -o /usr/share/keyrings/adoptium.gpg
    echo "deb [signed-by=/usr/share/keyrings/adoptium.gpg] https://packages.adoptium.net/artifactory/deb jammy main" |
      sudo tee /etc/apt/sources.list.d/adoptium.list >/dev/null
    sudo apt-get update
    sudo apt-get install -y "temurin-${JAVA_VERSION_REQUIRED}-jdk"
  else
    info "JDK ${java_version} (>= ${JAVA_VERSION_REQUIRED}) already present. Skipping install ..."
  fi

  # --- 1c. Resolve a JAVA_HOME whose javac major version is >= required -----
  # Prefer the exact Temurin build, then fall back to the highest JDK available.
  JAVA_HOME="$(resolve_java_home "$JAVA_VERSION_REQUIRED")"
  if [ -z "$JAVA_HOME" ]; then
    error "No JDK with javac >= ${JAVA_VERSION_REQUIRED} found under /usr/lib/jvm."
    error_exit "JPlag 6.x requires Java SE ${JAVA_VERSION_REQUIRED}. Aborting before the build."
  fi
  export JAVA_HOME
  export PATH="$JAVA_HOME/bin:$PATH"

  # --- 1d. Make this JDK the system default so every tool (incl. mvn) uses it
  sudo update-alternatives --install /usr/bin/java java "$JAVA_HOME/bin/java" 2000
  sudo update-alternatives --install /usr/bin/javac javac "$JAVA_HOME/bin/javac" 2000
  sudo update-alternatives --set java "$JAVA_HOME/bin/java"
  sudo update-alternatives --set javac "$JAVA_HOME/bin/javac"

  # --- 1e. Persist for future shells / manual re-runs ------------------------
  append_once_to_bashrc "export JAVA_HOME=$JAVA_HOME"
  append_once_to_bashrc 'export PATH=$JAVA_HOME/bin:$PATH'

  info "Using JAVA_HOME=$JAVA_HOME"
  info "java  -> $(java -version 2>&1 | head -n1)"
  info "javac -> $(javac -version 2>&1 | head -n1)"
}

install_maven() {
  info "2. Install Maven ${MAVEN_VERSION_REQUIRED}"

  local maven_version=0.0.0 maven_version_str maven_tgz
  if command -v mvn >/dev/null 2>&1; then
    maven_version_str="$(mvn --version 2>/dev/null | head -n 1 || true)"
    maven_version="$(printf '%s' "$maven_version_str" | awk '{print $3}')"
    [ -n "$maven_version" ] || maven_version=0.0.0
  fi

  if [ "$(printf '%s\n' "$MAVEN_VERSION_REQUIRED" "$maven_version" | sort -V | tail -n1)" = "$maven_version" ]; then
    info "Maven has already installed. Skipping ..."
    return 0
  fi

  maven_tgz="apache-maven-${MAVEN_VERSION_REQUIRED}-bin.tar.gz"
  sudo apt-get remove --purge -y maven || true
  wget "https://archive.apache.org/dist/maven/maven-3/${MAVEN_VERSION_REQUIRED}/binaries/${maven_tgz}"
  tar -xzf "${maven_tgz}"
  rm -f "${maven_tgz}"
  sudo rm -rf /opt/maven
  sudo mv "apache-maven-${MAVEN_VERSION_REQUIRED}" /opt/maven
  export M2_HOME=/opt/maven
  export PATH="$M2_HOME/bin:$PATH"
  append_once_to_bashrc 'export M2_HOME=/opt/maven'
  append_once_to_bashrc 'export PATH=$M2_HOME/bin:$PATH'
}

install_node() {
  info "3. Install Node.js ${NODE_VERSION_REQUIRED}"

  local node_version=0
  if command -v node >/dev/null 2>&1; then
    node_version="$(node --version 2>/dev/null | sed 's/^v//' | cut -d. -f1)"
  fi

  if [ "$node_version" -ge "$NODE_VERSION_REQUIRED" ]; then
    info "Node.js has already installed. Skipping ..."
    return 0
  fi

  sudo apt-get remove -y nodejs npm || true
  # Pinned to the same major the check above requires, so the two cannot drift.
  curl -fsSL "https://deb.nodesource.com/setup_${NODE_VERSION_REQUIRED}.x" | sudo -E bash -
  sudo apt-get install -y nodejs
}

install_jplag() {
  info "4. Install JPlag"

  if compgen -G "$HOME/jplag/cli/target/jplag-*-jar-with-dependencies.jar" >/dev/null; then
    info "JPlag has already installed. Skipping ..."
    return 0
  fi

  if [ -d "$HOME/jplag/.git" ]; then
    info "Existing jplag repository found. Pull latest changes ..."
    git -C "$HOME/jplag" pull --ff-only
  else
    rm -rf "$HOME/jplag"
    git clone https://github.com/jplag/jplag.git "$HOME/jplag"
  fi

  # Hard sanity check: the build MUST run on JDK >= required, or javac will
  # reject the "invalid target release: 25" and the whole reactor fails.
  local build_java_major jplag_jar
  build_java_major="$(java_major_of "$JAVA_HOME/bin/javac")"
  if [ -z "$build_java_major" ] || [ "$build_java_major" -lt "$JAVA_VERSION_REQUIRED" ]; then
    error "javac major is '${build_java_major}', but JPlag requires >= ${JAVA_VERSION_REQUIRED}."
    error_exit "Refusing to build with the wrong JDK (would fail: invalid target release)."
  fi

  # Pin JAVA_HOME explicitly for the Maven invocation so there is no ambiguity
  # about which javac the compiler plugin uses.
  (
    cd "$HOME/jplag" || exit 1
    JAVA_HOME="$JAVA_HOME" PATH="$JAVA_HOME/bin:$PATH" \
      mvn -P with-report-viewer clean package assembly:single \
      -pl cli,core,language-api,language-antlr-utils,languages/c,languages/cpp \
      -am \
      -DskipTests
  )

  jplag_jar="$(compgen -G "$HOME/jplag/cli/target/jplag-*-jar-with-dependencies.jar" | head -n 1 || true)"
  [ -n "$jplag_jar" ] || error_exit "JPlag build finished but no jar was produced."
  java -jar "$jplag_jar" --help >/dev/null 2>&1 ||
    error_exit "JPlag jar is not runnable: $jplag_jar"
}

install_marp() {
  info "5. Install Marp"

  if command -v marp >/dev/null 2>&1; then
    info "marp has already installed. Skipping ..."
    return 0
  fi

  sudo npm install -g npm
  sudo npm install -g @marp-team/marp-cli
  # engine.js resolves these from the repository root, so install them there
  # rather than in whatever directory this script happened to be invoked from.
  (cd "$SCRIPT_DIR" && npm i --save @marp-team/marp-core markdown-it-shiki)
}

install_firefox() {
  info "6. Install Firefox"

  if dpkg -s firefox >/dev/null 2>&1; then
    info "Firefox has already installed. Skipping ..."
    return 0
  fi

  sudo install -d -m 0755 /etc/apt/keyrings
  curl -fsSL https://packages.mozilla.org/apt/repo-signing-key.gpg |
    sudo gpg --dearmor --yes -o /etc/apt/keyrings/packages.mozilla.org.gpg

  echo "deb [signed-by=/etc/apt/keyrings/packages.mozilla.org.gpg] https://packages.mozilla.org/apt mozilla main" |
    sudo tee /etc/apt/sources.list.d/mozilla.list >/dev/null

  sudo tee /etc/apt/preferences.d/mozilla >/dev/null <<-'EOF'
	Package: firefox*
	Pin: origin packages.mozilla.org
	Pin-Priority: 1001
	EOF

  sudo apt-get update
  sudo apt-get install -y firefox
}

set_locale() {
  info "7. Set locale ${WANT_LOCALE}"

  if locale -a 2>/dev/null | grep -qiE '^en_US\.utf8$|^en_US\.UTF-8$'; then
    info "Locale has already set. Skipping ..."
    return 0
  fi

  sudo apt-get install -y locales
  if ! grep -qE '^\s*en_US\.UTF-8\s+UTF-8\b' /etc/locale.gen; then
    echo 'en_US.UTF-8 UTF-8' | sudo tee -a /etc/locale.gen >/dev/null
  fi
  sudo locale-gen
  sudo update-locale LANG="${WANT_LOCALE}" LC_ALL="${WANT_LOCALE}"
}

# The VS Code CLI is optional: this runs last and must never abort a run that
# has already installed every real dependency.
install_vscode_extensions() {
  info "(Opt.) Install VSCode extensions"

  if ! command -v code >/dev/null 2>&1; then
    warn "VS Code CLI ('code') not found. Skipping extension install ..."
    return 0
  fi

  local installed ext
  installed="$(code --list-extensions 2>/dev/null || true)"

  for ext in "${VSCODE_EXTENSIONS[@]}"; do
    if printf '%s\n' "$installed" | grep -Fqx "$ext"; then
      info "Extension $ext is already installed. Skipping ..."
      continue
    fi
    info "Installing VSCode extension: ${ext}"
    code --install-extension "$ext" || warn "Failed to install extension: ${ext}"
  done
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  trap on_error ERR

  # Keep apt from opening dialogs (service restarts, config conflicts) so an
  # unattended run cannot hang waiting for input.
  export DEBIAN_FRONTEND=noninteractive

  # Active sudo and snap (chrome dependency)
  sudo apt-get update
  sudo apt-get upgrade --with-new-pkgs -y
  sudo apt-get install -y snapd curl git wget apt-transport-https gnupg

  install_java
  install_maven
  install_node
  install_jplag
  install_marp
  install_firefox
  set_locale

  info "8. Install fonts"
  apt_install_missing "${FONT_PKGS[@]}"

  info "9. Install pdfinfo (poppler-utils), imagemagick, and unzip"
  apt_install_missing "${TOOL_PKGS[@]}"

  install_vscode_extensions

  # Clean. Only the cached lists are removed; the directory itself must stay,
  # or the next `apt-get update` warns about the missing path.
  sudo apt-get clean
  sudo rm -rf /var/lib/apt/lists/*
  info "Done."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
