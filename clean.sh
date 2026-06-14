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
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# ?/, ""); print}' "$0"
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

  for target in c cpp; do
    local script="${SCRIPT_DIR}/${target}/clean.sh"
    [ -f "${script}" ] || error_exit "clean.sh not found: ${script}"
    info "Running ${target}/clean.sh ..."
    bash "${script}"
  done

  info "All clean complete."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
