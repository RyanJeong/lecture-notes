#!/usr/bin/env bash

# ============================================================================
# jplag.sh
# ============================================================================
# Usage:
#   ./jplag.sh
#
# Description:
#   Run JPlag plagiarism detection over every numeric submission directory in
#   the current directory, writing one result archive per directory.
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./jplag.sh
#
# Dependencies:
#   java, JPlag jar built at ${HOME}/jplag (see repository README)
#
# ============================================================================

set -euo pipefail

color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly JPLAG_GLOB="${HOME}/jplag/cli/target/jplag-*-jar-with-dependencies.jar"
readonly LANGUAGE="cpp"

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

run_jplag() {
  local jar="$1"
  local dir_name
  local found=0

  while IFS= read -r dir_name; do
    found=1
    info "Comparing: ${dir_name}"
    (
      cd "${dir_name}" || exit 1
      java -jar "${jar}" \
        -l "${LANGUAGE}" \
        -M run \
        --overwrite ./
    )
  done < <(find . -maxdepth 1 -mindepth 1 -type d -exec basename {} \; | grep -E '^[0-9_]+$' | sort)

  [[ "${found}" -eq 1 ]] || warn "No numeric submission directories found."
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  command -v java >/dev/null 2>&1 || error_exit "java not found in PATH"

  local jar
  jar="$(resolve_jplag_jar)"
  run_jplag "${jar}"

  info "Run 'viewer.sh <ASMT_DEST_DIR>' to check similarity results and decide"
  info "whether to reject scoring due to high similarity."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
