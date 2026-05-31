#!/usr/bin/env bash

# ============================================================================
# check_syntax.sh
# ============================================================================
# Usage:
#   ./check_syntax.sh [DIR]
#
# Description:
#   Check ANSI C syntax for all .c files under */src/
#   (excluding *_part* and *_ignore*).
#   If a Makefile is found, also runs make to verify the build.
#   Results are written to error_file_lists.txt in the script directory.
#
# Arguments:
#   DIR   Optional subdirectory to scan (e.g., 00, 04).
#         If omitted, all numbered directories are processed.
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./check_syntax.sh
#   ./check_syntax.sh 04
#
# ============================================================================

set -euo pipefail

# Color output functions (compatible with macOS and Linux)
color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_cyan() { printf '\033[36m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly ERROR_FILE="${SCRIPT_DIR}/error_file_lists.txt"
readonly GCC_FLAGS="-c -fsyntax-only -ansi -Wall -Wextra -Werror -Wno-trigraphs -trigraphs -fno-builtin"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# ?/, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

check_files() {
  local scan_dir="$1"

  while IFS= read -r -d '' file; do
    local basename
    basename="$(basename "${file}")"

    if [[ "${basename}" == *_part* || "${basename}" == *_ignore* ]]; then
      info "Skip: ${file}"
      continue
    fi

    info "Check: ${file}"
    if ! gcc "${file}" ${GCC_FLAGS} >/dev/null 2>&1; then
      printf '%s\n' "${file}" >>"${ERROR_FILE}"
      gcc "${file}" ${GCC_FLAGS} >>"${ERROR_FILE}" 2>&1 || true
      printf '%s\n' "========================================" >>"${ERROR_FILE}"
      ERROR_COUNT=$((ERROR_COUNT + 1))
    fi
  done < <(find "${scan_dir}" -name "*.c" -print0 | sort -z)
}

check_makefiles() {
  local scan_dir="$1"

  while IFS= read -r -d '' makefile; do
    local dir
    dir="$(dirname "${makefile}")"
    info "Build: ${dir}"
    if ! make -C "${dir}" >/dev/null 2>&1; then
      printf '%s\n' "${makefile}" >>"${ERROR_FILE}"
      make -C "${dir}" >>"${ERROR_FILE}" 2>&1 || true
      printf '%s\n' "========================================" >>"${ERROR_FILE}"
      ERROR_COUNT=$((ERROR_COUNT + 1))
    fi
    make -C "${dir}" clean >/dev/null 2>&1 || true
  done < <(find "${scan_dir}" -name "Makefile" -print0 | sort -z)
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  ERROR_COUNT=0
  >"${ERROR_FILE}"

  local scan_dirs=()

  if [ -n "${1:-}" ]; then
    local candidate="${SCRIPT_DIR}/${1}/src"
    if [ -d "${candidate}" ]; then
      scan_dirs+=("${candidate}")
      info "Scanning directory: ${candidate}"
    else
      warn "src directory not found: ${candidate}"
      info "No src directory to check. Exiting safely."
      exit 0
    fi
  else
    local dir
    for dir in "${SCRIPT_DIR}"/[0-9][0-9]; do
      if [ -d "${dir}/src" ]; then
        scan_dirs+=("${dir}/src")
      fi
    done
    if [ "${#scan_dirs[@]}" -eq 0 ]; then
      warn "No src directories found under ${SCRIPT_DIR}"
      info "Nothing to check. Exiting safely."
      exit 0
    fi
    info "Scanning all src/ directories"
  fi

  local scan_dir
  for scan_dir in "${scan_dirs[@]}"; do
    check_files "${scan_dir}"
    check_makefiles "${scan_dir}"
  done

  if [ -s "${ERROR_FILE}" ]; then
    warn "${ERROR_COUNT} error(s) found. See: ${ERROR_FILE}"
    cat "${ERROR_FILE}"
  else
    info "All files passed syntax check."
  fi
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
