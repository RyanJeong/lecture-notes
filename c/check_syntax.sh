#!/usr/bin/env bash

# ============================================================================
# check_syntax.sh
# ============================================================================
# Usage:
#   ./check_syntax.sh [DIR]
#
# Description:
#   Check ANSI C syntax for all .c files (excluding *_part* and *_ignore*).
#   Results are written to error_file_lists.txt in the script directory.
#
# Arguments:
#   DIR   Optional subdirectory to scan (e.g., 00, 04).
#         If omitted or not found, all subdirectories are scanned.
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
readonly GCC_FLAGS="-c -fsyntax-only -ansi -Wall -Wextra -Werror -fno-builtin"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# ?/, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

check_files() {
  local scan_dir="$1"
  local error_count=0

  >"${ERROR_FILE}"

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
      error_count=$((error_count + 1))
    fi
  done < <(find "${scan_dir}" -name "*.c" -print0 | sort -z)

  if [ -s "${ERROR_FILE}" ]; then
    warn "${error_count} file(s) with errors. See: ${ERROR_FILE}"
    cat "${ERROR_FILE}"
  else
    info "All files passed syntax check."
  fi
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  local scan_dir="${SCRIPT_DIR}"

  if [ -n "${1:-}" ]; then
    local candidate="${SCRIPT_DIR}/${1}"
    if [ -d "${candidate}" ]; then
      scan_dir="${candidate}"
      info "Scanning directory: ${scan_dir}"
    else
      warn "Directory not found: ${candidate} -- scanning all directories."
    fi
  fi

  check_files "${scan_dir}"
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
