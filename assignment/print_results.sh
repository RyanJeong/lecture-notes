#!/usr/bin/env bash

# ============================================================================
# print_results.sh
# ============================================================================
# Usage:
#   ./print_results.sh
#
# Description:
#   Print every results.txt found under the current directory, skipping the
#   backup/ tree.
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./print_results.sh
#
# ============================================================================

set -euo pipefail

color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

print_results() {
  local file
  local found=0

  while IFS= read -r -d '' file; do
    found=1
    info "${file}"
    cat -- "${file}"
    printf '\n'
  done < <(find . -name results.txt -not -path './backup/*' -print0 | sort -z)

  [[ "${found}" -eq 1 ]] || warn "No results.txt found."
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  print_results
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
