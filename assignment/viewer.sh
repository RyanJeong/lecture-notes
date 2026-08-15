#!/usr/bin/env bash

# ============================================================================
# viewer.sh
# ============================================================================
# Usage:
#   ./viewer.sh <JPLAG_RESULT_PATH>
#
# Description:
#   Open the JPlag report viewer for a previously generated result archive.
#
# Arguments:
#   JPLAG_RESULT_PATH   Directory containing results.jplag
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./viewer.sh ./202512345
#
# Dependencies:
#   java, JPlag jar built at ${HOME}/jplag (see repository README)
#
# ============================================================================

set -euo pipefail

color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly SCRIPT_NAME="$(basename "$0")"
readonly JPLAG_GLOB="${HOME}/jplag/cli/target/jplag-*-jar-with-dependencies.jar"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

# Expand the versioned jar glob to a single path.
resolve_jplag_jar() {
  local -a jars=()
  local jar

  for jar in ${JPLAG_GLOB}; do
    [[ -f "${jar}" ]] && jars+=("${jar}")
  done

  [[ "${#jars[@]}" -gt 0 ]] || error_exit "JPlag jar not found: ${JPLAG_GLOB}"
  printf '%s' "${jars[0]}"
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  local result_path="${1:-}"
  [[ -n "${result_path}" ]] || error_exit "Usage: ${SCRIPT_NAME} <JPLAG_RESULT_PATH>"

  local result_file="${result_path}/results.jplag"
  [[ -f "${result_file}" ]] || error_exit "Result file not found: ${result_file}"

  command -v java >/dev/null 2>&1 || error_exit "java not found in PATH"

  local jar
  jar="$(resolve_jplag_jar)"

  info "Opening viewer for ${result_file}"
  java -jar "${jar}" \
    -M view \
    --result-file="${result_file}"
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
