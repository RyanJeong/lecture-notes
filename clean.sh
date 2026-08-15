#!/usr/bin/env bash

# ============================================================================
# clean.sh
# ============================================================================
# Usage:
#   ./clean.sh
#
# Description:
#   Run clean.sh for both c/ and cpp/ subdirectories.
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
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  # Every course directory owns a clean.sh, so new courses are picked up
  # without editing this list.
  local found=0
  local script
  for script in "${SCRIPT_DIR}"/*/clean.sh; do
    [ -f "${script}" ] || continue
    found=1
    info "Running $(basename "$(dirname "${script}")")/clean.sh ..."
    bash "${script}"
  done

  [ "${found}" -eq 1 ] || error_exit "No course clean.sh found under ${SCRIPT_DIR}"

  info "All clean complete."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
