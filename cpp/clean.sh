#!/usr/bin/env bash

# ============================================================================
# clean.sh
# ============================================================================
# Usage:
#   ./clean.sh
#
# Description:
#   Remove generated files: temp.pdf, temp.md, temp.pptx, a.out,
#   object files (.o), extensionless binaries, and error_file_lists.txt.
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./clean.sh
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

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

remove_if_exists() {
  local file="$1"
  if [ -e "${file}" ]; then
    info "Remove: ${file}"
    rm -- "${file}"
  fi
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  info "Cleaning generated files under: ${SCRIPT_DIR}"

  # Remove named generated files
  while IFS= read -r -d '' file; do
    remove_if_exists "${file}"
  done < <(find "${SCRIPT_DIR}" -type f \( -name "temp.pdf" -o -name "temp.md" -o -name "temp.pptx" -o -name "a.out" \) -print0)

  # Remove extensionless executables (binary files without a dot in filename)
  while IFS= read -r -d '' file; do
    remove_if_exists "${file}"
  done < <(find "${SCRIPT_DIR}" -type f ! -name '*.*' ! -name 'Makefile' -print0)

  # Remove object files (.o)
  while IFS= read -r -d '' file; do
    remove_if_exists "${file}"
  done < <(find "${SCRIPT_DIR}" -type f -name "*.o" -print0)

  # Remove error_file_lists.txt
  while IFS= read -r -d '' file; do
    remove_if_exists "${file}"
  done < <(find "${SCRIPT_DIR}" -name "error_file_lists.txt" -print0)

  # Run make clean in directories containing a Makefile
  while IFS= read -r -d '' makefile; do
    local dir
    dir="$(dirname "${makefile}")"
    info "Run make clean in: ${dir}"
    make -C "${dir}" clean >/dev/null 2>&1
  done < <(find "${SCRIPT_DIR}" -name "Makefile" -print0)

  info "Clean complete."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
