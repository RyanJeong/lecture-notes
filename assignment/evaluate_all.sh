#!/usr/bin/env bash

# ============================================================================
# evaluate_all.sh
# ============================================================================
# Usage:
#   ./evaluate_all.sh [OPTIONS] <ASMT_DEST_DIR> <DATASET_DIR>
#
# Description:
#   Grade every submission under ASMT_DEST_DIR using the assignment's own
#   check.sh, which compiles each submission and scores it. The same command
#   works for C and C++ assignments: the grader lives with the dataset, so no
#   separate compile step is needed.
#
#   Output is printed and also written to ASMT_DEST_DIR/results.txt, ending
#   with a SUMMARY block of "<student>: <score>" lines.
#
# Arguments:
#   ASMT_DEST_DIR   Directory holding one sub-directory per student
#   DATASET_DIR     Assignment directory containing check.sh and in*/out* files
#
# Options:
#   -h, --help     Show this help message
#   -d, --docker   Grade inside a Linux container. Required on macOS, which
#                  ships no timeout(1) and whose clang differs from gcc.
#       --image N  Container image to use (default: gcc:13)
#
# Examples:
#   ./evaluate_all.sh ./2026_1_565006_01_1614899 ./dju-asmt/asmt1-c
#   ./evaluate_all.sh --docker ./2026_1_565006_01_2618307 ./dju-asmt/asmt2-c
#   ./evaluate_all.sh --docker ./2025_2_564016_01_3586204 ./dju-asmt/asmt3-cpp
#
# Dependencies:
#   gcc, g++, timeout (GNU coreutils); or docker with --docker
#
# ============================================================================

set -euo pipefail

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
readonly RESULTS_NAME="results.txt"
readonly DEFAULT_IMAGE="dju-grader"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

# Path relative to SCRIPT_DIR, so the same value works on the host and inside
# the container (which mounts SCRIPT_DIR at /workspace).
relative_to_script_dir() {
  local path="$1"
  local resolved
  resolved="$(cd "${path}" 2>/dev/null && pwd)" || error_exit "Directory not found: ${path}"
  case "${resolved}" in
  "${SCRIPT_DIR}") printf '.' ;;
  "${SCRIPT_DIR}"/*) printf '%s' "${resolved#"${SCRIPT_DIR}/"}" ;;
  *) error_exit "Must live under ${SCRIPT_DIR}: ${path}" ;;
  esac
}

# Build the grading image on first use, then re-run this script inside it.
ensure_image() {
  local image="$1"

  docker image inspect "${image}" >/dev/null 2>&1 && return 0

  [ -f "${SCRIPT_DIR}/Dockerfile" ] || error_exit "Dockerfile not found: ${SCRIPT_DIR}/Dockerfile"
  info "Building image ${image} (first run only)..."
  docker build -q -t "${image}" "${SCRIPT_DIR}" >/dev/null ||
    error_exit "Failed to build ${image}"
  info "Image ready."
}

run_in_docker() {
  local image="$1"
  local dest_rel="$2"
  local data_rel="$3"

  command -v docker >/dev/null 2>&1 || error_exit "docker not found in PATH"
  docker info >/dev/null 2>&1 || error_exit "docker daemon is not running"
  ensure_image "${image}"

  info "Grading inside ${image} ..."
  docker run --rm \
    --user "$(id -u):$(id -g)" \
    -v "${SCRIPT_DIR}":/workspace \
    -w /workspace \
    "${image}" \
    bash "./${SCRIPT_NAME}" "${dest_rel}" "${data_rel}"
}

grade() {
  local dest_dir="$1"
  local data_dir="$2"
  local results_file="${dest_dir}/${RESULTS_NAME}"
  local status=0

  step "Grading ${dest_dir} with $(basename "${data_dir}")"

  # check.sh exits non-zero for a single submission below full marks; in batch
  # mode it exits 0. Either way the report is what matters, so the status is
  # captured rather than allowed to abort the run.
  "${data_dir}/check.sh" "${dest_dir}" 2>&1 | tee "${results_file}" || status=$?

  printf '\n'
  if grep -q '^==================== SUMMARY' "${results_file}"; then
    local graded perfect failed
    graded=$(sed -n '/^==================== SUMMARY/,$p' "${results_file}" | grep -c ': ' || true)
    perfect=$(sed -n '/^==================== SUMMARY/,$p' "${results_file}" | grep -c ': 10$' || true)
    failed=$(sed -n '/^==================== SUMMARY/,$p' "${results_file}" | grep -c 'compilation failed' || true)
    info "Graded ${graded} submission(s): ${perfect} full marks, ${failed} failed to compile"
  else
    warn "No SUMMARY block produced (single-submission mode, exit ${status})"
  fi
  info "Report written to ${results_file}"
}

main() {
  local use_docker="false"
  local image="${DEFAULT_IMAGE}"
  local -a positional=()

  while [ "$#" -gt 0 ]; do
    case "$1" in
    -h | --help)
      show_help
      exit 0
      ;;
    -d | --docker)
      use_docker="true"
      ;;
    --image)
      shift
      [ "$#" -gt 0 ] || error_exit "--image requires a value"
      image="$1"
      ;;
    -*)
      error_exit "Unknown option: $1"
      ;;
    *)
      positional+=("$1")
      ;;
    esac
    shift
  done

  if [ "${#positional[@]}" -ne 2 ]; then
    error "Usage: ${SCRIPT_NAME} [OPTIONS] <ASMT_DEST_DIR> <DATASET_DIR>"
    show_help
    exit 1
  fi

  local dest_dir="${positional[0]}"
  local data_dir="${positional[1]}"

  [ -d "${dest_dir}" ] || error_exit "ASMT_DEST_DIR not found: ${dest_dir}"
  [ -d "${data_dir}" ] || error_exit "DATASET_DIR not found: ${data_dir}"
  [ -x "${data_dir}/check.sh" ] || error_exit "check.sh not found or not executable in: ${data_dir}"

  local dest_rel data_rel
  dest_rel="$(relative_to_script_dir "${dest_dir}")"
  data_rel="$(relative_to_script_dir "${data_dir}")"

  if [ "${use_docker}" = "true" ]; then
    run_in_docker "${image}" "${dest_rel}" "${data_rel}"
    return $?
  fi

  command -v timeout >/dev/null 2>&1 ||
    error_exit "timeout(1) not found. On macOS run '${SCRIPT_NAME} --docker' instead."

  cd "${SCRIPT_DIR}"
  grade "${dest_rel}" "${data_rel}"
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
