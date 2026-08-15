#!/usr/bin/env bash

# ============================================================================
# ci.sh
# ============================================================================
# Usage:
#   ./ci.sh [OPTIONS] [COURSE...]
#
# Description:
#   Run the GitHub Actions workflow locally in a single pass: syntax-check
#   every source file, then build and validate every chapter, leaving the
#   PDF/PPTX artifacts under release/.
#
#   Mirrors .github/workflows/build.yml. A failing chapter does not stop the
#   run; every chapter is attempted and a summary is printed at the end.
#
# Arguments:
#   COURSE   Course directories to run (e.g. c, cpp). Defaults to all
#            top-level directories containing a check_syntax.sh.
#
# Options:
#   -h, --help     Show this help message
#   -d, --docker   Run inside a Linux container. Required on macOS, where
#                  check_and_release.sh needs GNU grep -oP and ImageMagick.
#
# Examples:
#   ./ci.sh
#   ./ci.sh cpp
#   ./ci.sh --docker
#   ./ci.sh --docker c
#
# Dependencies:
#   node, marp, gcc, g++, pdfinfo, pdftoppm (poppler-utils),
#   convert, identify (imagemagick), GNU grep
#   With --docker: only docker is required.
#
# ============================================================================

set -euo pipefail

# Color output functions (compatible with macOS and Linux)
color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_cyan() { printf '\033[36m'; }
color_bold() { printf '\033[1m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }
step() { printf '%s\n' "$(color_cyan)[STEP]$(color_reset) $(color_bold)${1:-}$(color_reset)"; }

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly SCRIPT_NAME="$(basename "$0")"
readonly DOCKER_IMAGE="lecture-notes-ci"
readonly RELEASE_DIR="${SCRIPT_DIR}/release"

# A course is any top-level directory owning a check_syntax.sh, so adding a
# new course requires no change here.
discover_courses() {
  local script
  for script in "${SCRIPT_DIR}"/*/check_syntax.sh; do
    [ -f "${script}" ] || continue
    basename "$(dirname "${script}")"
  done
}

# Newline-delimited "<status> <chapter>" records; kept as a string so the
# script stays compatible with the bash 3.2 shipped on macOS.
RESULTS=""
FAILED=0

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

record() {
  RESULTS="${RESULTS}${1} ${2}"$'\n'
  [ "$1" = "OK" ] || FAILED=$((FAILED + 1))
}

# -- Dependency check --------------------------------------------------------

check_dependencies() {
  local missing=""
  local tool

  for tool in node gcc g++ pdfinfo pdftoppm convert identify; do
    command -v "${tool}" >/dev/null 2>&1 || missing="${missing} ${tool}"
  done

  # check_and_release.sh calls `marp` directly, not via npx.
  command -v marp >/dev/null 2>&1 || missing="${missing} marp"

  # check_and_release.sh uses grep -oP, which BSD grep does not support.
  if ! printf 'x' | grep -qP 'x' 2>/dev/null; then
    missing="${missing} grep(GNU,-P)"
  fi

  if [ -n "${missing}" ]; then
    error "Missing dependencies:${missing}"
    error "Run '${SCRIPT_NAME} --docker' to execute in a Linux container instead."
    exit 1
  fi

  if [ ! -d "${SCRIPT_DIR}/node_modules/markdown-it-shiki" ]; then
    info "Installing local marp plugins (engine.js dependencies)..."
    (cd "${SCRIPT_DIR}" && npm install --no-audit --no-fund \
      @marp-team/marp-core markdown-it-shiki >/dev/null)
  fi
}

# -- Docker mode -------------------------------------------------------------

build_docker_image() {
  if docker image inspect "${DOCKER_IMAGE}" >/dev/null 2>&1; then
    info "Reusing image: ${DOCKER_IMAGE}"
    return 0
  fi

  info "Building image ${DOCKER_IMAGE} (first run only, takes a few minutes)..."
  local context
  context="$(mktemp -d)"

  cat >"${context}/Dockerfile" <<'DOCKERFILE'
FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update -qq && apt-get install -y -qq --no-install-recommends \
      curl ca-certificates gnupg poppler-utils imagemagick \
      fonts-noto-cjk fonts-noto-cjk-extra gcc g++ make \
 && curl -fsSL https://deb.nodesource.com/setup_22.x | bash - \
 && apt-get install -y -qq nodejs \
 && curl -fsSL https://dl.google.com/linux/linux_signing_key.pub \
      | gpg --dearmor -o /usr/share/keyrings/google-chrome.gpg \
 && echo "deb [signed-by=/usr/share/keyrings/google-chrome.gpg] http://dl.google.com/linux/chrome/deb/ stable main" \
      > /etc/apt/sources.list.d/google-chrome.list \
 && apt-get update -qq && apt-get install -y -qq google-chrome-stable \
 && npm install -g @marp-team/marp-cli \
 && rm -rf /var/lib/apt/lists/*
ENV CHROME_PATH=/usr/bin/google-chrome
DOCKERFILE

  if ! docker build -q -t "${DOCKER_IMAGE}" "${context}" >/dev/null; then
    rm -rf "${context}"
    error_exit "Failed to build ${DOCKER_IMAGE}"
  fi
  rm -rf "${context}"
  info "Image ready."
}

run_in_docker() {
  command -v docker >/dev/null 2>&1 || error_exit "docker not found in PATH"
  docker info >/dev/null 2>&1 || error_exit "docker daemon is not running"

  build_docker_image

  info "Running ${SCRIPT_NAME} inside ${DOCKER_IMAGE}..."
  docker run --rm \
    -v "${SCRIPT_DIR}":/workspace \
    -w /workspace \
    --shm-size=1g \
    "${DOCKER_IMAGE}" \
    bash "./${SCRIPT_NAME}" "$@"
}

# -- Workflow steps ----------------------------------------------------------

# Mirrors the "Syntax-check all sources" step: building only compiles the
# sources embedded whole in slides, so this scans every file under src/.
syntax_check_lang() {
  local lang="$1"

  step "${lang}: syntax-check all sources"
  if "${SCRIPT_DIR}/${lang}/check_syntax.sh"; then
    record "OK" "${lang}:syntax"
    return 0
  fi

  error "${lang}: syntax check failed (see ${lang}/error_file_lists.txt)"
  record "FAIL" "${lang}:syntax"
  return 1
}

# Paths stay relative to the repository root: check_and_release.sh derives the
# course and chapter from dirname, so an absolute path would place artifacts in
# release/<abs>/<path>/ instead of release/<course>/.
run_chapter() {
  local chapter="$1"

  step "${chapter}: build"
  if ! ./build.sh \
    "${chapter}/README.md" "${chapter}/temp.md" "${chapter}/temp.pdf"; then
    error "${chapter}: build failed"
    record "FAIL" "${chapter} (build)"
    return 0
  fi

  step "${chapter}: check and release"
  if ! ./check_and_release.sh "${chapter}/temp.pdf"; then
    error "${chapter}: check failed"
    record "FAIL" "${chapter} (check)"
    return 0
  fi

  record "OK" "${chapter}"
}

run_lang() {
  local lang="$1"

  [ -d "${SCRIPT_DIR}/${lang}" ] || error_exit "Unknown course directory: ${lang}"

  # Start from a clean artifact set so the summary reflects only this run.
  if [ -d "${RELEASE_DIR}/${lang}" ]; then
    info "Clearing previous artifacts: release/${lang}"
    rm -rf "${RELEASE_DIR:?}/${lang}"
  fi

  syntax_check_lang "${lang}" || true

  local dir
  local found=0
  for dir in "${lang}"/[0-9][0-9]; do
    [ -d "${dir}" ] || continue
    found=1
    run_chapter "${dir}"
  done

  [ "${found}" -eq 1 ] || warn "No chapters found under ${lang}/"
}

# -- Summary -----------------------------------------------------------------

print_summary() {
  printf '\n'
  printf '%s\n' "============================================================"
  printf '%s\n' "$(color_bold)SUMMARY$(color_reset)"
  printf '%s\n' "============================================================"

  local status name
  while read -r status name; do
    [ -n "${status}" ] || continue
    if [ "${status}" = "OK" ]; then
      printf '  %sPASS%s  %s\n' "$(color_green)" "$(color_reset)" "${name}"
    else
      printf '  %sFAIL%s  %s\n' "$(color_red)" "$(color_reset)" "${name}"
    fi
  done <<EOF
${RESULTS}
EOF

  printf '\n'
  if [ -d "${RELEASE_DIR}" ]; then
    local count
    count=$(find "${RELEASE_DIR}" -type f \( -name '*.pdf' -o -name '*.pptx' \) | wc -l | tr -d ' ')
    info "Artifacts (${count} files) in: release/"
    find "${RELEASE_DIR}" -type f \( -name '*.pdf' -o -name '*.pptx' \) |
      sed "s|${SCRIPT_DIR}/|  |" | sort
  else
    warn "No artifacts produced."
  fi

  printf '\n'
  if [ "${FAILED}" -eq 0 ]; then
    info "All steps passed."
    return 0
  fi
  error "${FAILED} step(s) failed."
  return 1
}

# -- Main --------------------------------------------------------------------

main() {
  local use_docker="false"
  local langs=""
  local available
  available="$(discover_courses | tr '\n' ' ')"

  [ -n "${available}" ] || error_exit "No course directories found (need <course>/check_syntax.sh)"

  while [ "$#" -gt 0 ]; do
    case "$1" in
    -h | --help)
      show_help
      printf '\n%s\n' "Available courses: ${available}"
      exit 0
      ;;
    -d | --docker)
      use_docker="true"
      ;;
    -*)
      error "Unknown option: $1"
      show_help
      exit 1
      ;;
    *)
      case " ${available} " in
      *" $1 "*) langs="${langs} $1" ;;
      *) error_exit "Unknown course: $1 (available: ${available})" ;;
      esac
      ;;
    esac
    shift
  done

  [ -n "${langs}" ] || langs="${available}"

  if [ "${use_docker}" = "true" ]; then
    run_in_docker ${langs}
    return $?
  fi

  cd "${SCRIPT_DIR}"
  check_dependencies

  local lang
  for lang in ${langs}; do
    run_lang "${lang}"
  done

  print_summary
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
