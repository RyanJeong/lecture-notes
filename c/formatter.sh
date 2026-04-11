#!/usr/bin/env bash

# ============================================================================
# formatter.sh
# ============================================================================
# Usage:
#   ./formatter.sh [DIR]
#
# Description:
#   Format all .c and .h files under */src/ using clang-format
#   with K&R style. File permissions are set to 755 after formatting.
#
# Arguments:
#   DIR   Optional subdirectory to format (e.g., 00, 04).
#         If omitted, all numbered directories are processed.
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./formatter.sh
#   ./formatter.sh 04
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
readonly CLANG_FORMAT_STYLE="file:${HOME}/clang-format/.clang-format-knr"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# ?/, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

format_files() {
  local scan_dir="$1"

  command -v clang-format >/dev/null || error_exit "clang-format not found in PATH"

  while IFS= read -r -d '' file; do
    info "Format: ${file}"
    clang-format --style="${CLANG_FORMAT_STYLE}" -i "${file}"
    chmod 755 "${file}"
  done < <(find "${scan_dir}" \( -name "*.c" -o -name "*.h" \) -print0 | sort -z)

  info "Formatting complete."
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  local scan_dirs=()

  if [ -n "${1:-}" ]; then
    local candidate="${SCRIPT_DIR}/${1}/src"
    if [ -d "${candidate}" ]; then
      scan_dirs+=("${candidate}")
      info "Formatting directory: ${candidate}"
    else
      error_exit "Directory not found: ${SCRIPT_DIR}/${1}"
    fi
  else
    local dir
    for dir in "${SCRIPT_DIR}"/[0-9][0-9]; do
      if [ -d "${dir}/src" ]; then
        scan_dirs+=("${dir}/src")
      fi
    done
    info "Formatting all src/ directories"
  fi

  local scan_dir
  for scan_dir in "${scan_dirs[@]}"; do
    format_files "${scan_dir}"
  done
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
