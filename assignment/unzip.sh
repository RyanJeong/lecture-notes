#!/usr/bin/env bash

# ============================================================================
# unzip.sh
# ============================================================================
# Usage:
#   ./unzip.sh [OPTIONS]
#
# Description:
#   Extract every submission .zip in the script's directory into a sanitized
#   directory name, strip files that are not part of a submission, and back up
#   the cleaned tree.
#
#   Submission archives are named like:
#     <course>(<year>, <term>, <code>, <class>)-<assignment>-<id>.zip
#   Commas are dropped, spaces become underscores, and any remaining character
#   outside [0-9A-Za-z_] is removed to form the target directory name.
#
#   Files whose extension is not a C/C++ source or header are listed in
#   results.txt inside each submission directory.
#
# Options:
#   -h, --help     Show this help message
#   -d, --docker   Extract inside a Linux container. Recommended on macOS,
#                  whose unzip mangles the Korean student names in the LMS
#                  archives and would corrupt the ids in the grade report.
#       --image N  Container image to use (default: dju-grader)
#
# Examples:
#   ./unzip.sh
#   ./unzip.sh --docker
#
# Dependencies:
#   unzip; or docker with --docker
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

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly SCRIPT_NAME="$(basename "$0")"
readonly BACKUP_DIR="${SCRIPT_DIR}/backup"
readonly RESULT_FILE="results.txt"
readonly DEFAULT_IMAGE="dju-grader"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

# Drop commas, turn spaces into underscores, keep only [0-9A-Za-z_].
sanitize_name() {
  local base_name="$1"
  printf '%s' "${base_name}" | sed -e 's/,//g' -e 's/ /_/g' -e 's/[^0-9a-zA-Z_]//g'
}

remove_noise_files() {
  local file name new_name

  # 1. Vendor "online" artifacts
  rm -rf -- *online* 2>/dev/null || true

  # 2. Hidden files
  while IFS= read -r -d '' file; do
    [[ "${file}" == "." ]] && continue
    rm -rf -- "${file}"
  done < <(find . -name ".*" -mindepth 1 -print0)

  # 3. Spaces in top-level names
  for name in *; do
    if [[ "${name}" == *" "* ]]; then
      new_name="${name// /_}"
      mv -- "${name}" "${new_name}"
    fi
  done
}

# Nested archives often carry directory modes without the owner write bit,
# which later makes the backup copy fail. chmod needs no privileges here since
# the extracting user owns the files.
repair_permissions() {
  chmod -R u+rwX ./ 2>/dev/null || true

  # Ownership only needs repairing when some other user extracted the files.
  # That requires sudo, and is unnecessary inside the container.
  if command -v sudo >/dev/null 2>&1 && [[ -n "${USER:-}" ]] && [[ "$(id -u)" -ne 0 ]]; then
    sudo chown -R "${USER}":"${USER}" ./ 2>/dev/null || true
  fi
}

# Nested archives are extracted in place; anything else that is not a C/C++
# source or header is recorded for manual review.
report_foreign_files() {
  local file dir_path file_name lower_file

  : >"./${RESULT_FILE}"

  while IFS= read -r -d '' file; do
    [[ "${file}" == "./${RESULT_FILE}" ]] && continue

    if [[ "${file,,}" == *.zip ]]; then
      dir_path="${file%/*}"
      file_name="${file##*/}"
      lower_file="${dir_path}/${file_name,,}"
      if [[ "${file}" != "${lower_file}" ]]; then
        mv -- "${file}" "${lower_file}"
        file="${lower_file}"
      fi
      # Exit code 1 can still mean success with warnings, so it is ignored.
      unzip "${file}" -d "${dir_path}" >/dev/null 2>&1 || true
      if ! ls -A "${dir_path}" | grep -v "$(basename "${file}")" >/dev/null 2>&1; then
        printf '>>>> %s\n' "${file}" >>"./${RESULT_FILE}"
      fi
    else
      printf '>>>> %s\n' "${file}" >>"./${RESULT_FILE}"
    fi
  done < <(find . -type f \
    ! \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.cxx" \
    -o -name "*.h" -o -name "*.hpp" \) -print0)
}

process_archive() {
  local zip_file="$1"
  local base_name target_dir

  info "Processing: ${zip_file}"

  base_name="$(basename "${zip_file}" .zip)"
  target_dir="$(sanitize_name "${base_name}")"
  [[ -n "${target_dir}" ]] || error_exit "Empty target directory for: ${zip_file}"

  mkdir -p "${target_dir}"
  unzip -q "${zip_file}" -d "${target_dir}"
  info "-> Extracted to: ${target_dir}"

  (
    cd "${target_dir}" || exit 1
    remove_noise_files
    report_foreign_files
    repair_permissions
  )

  info "-> Successfully filtered unnecessary files"

  cp -r "${target_dir}" "${BACKUP_DIR}"
  info "-> Successfully backed up to ${BACKUP_DIR}"
}

# Build the grading image on first use, then re-run this script inside it.
ensure_image() {
  local image="$1"

  docker image inspect "${image}" >/dev/null 2>&1 && return 0

  [[ -f "${SCRIPT_DIR}/Dockerfile" ]] || error_exit "Dockerfile not found: ${SCRIPT_DIR}/Dockerfile"
  info "Building image ${image} (first run only)..."
  docker build -q -t "${image}" "${SCRIPT_DIR}" >/dev/null ||
    error_exit "Failed to build ${image}"
  info "Image ready."
}

run_in_docker() {
  local image="$1"

  command -v docker >/dev/null 2>&1 || error_exit "docker not found in PATH"
  docker info >/dev/null 2>&1 || error_exit "docker daemon is not running"
  ensure_image "${image}"

  info "Extracting inside ${image}..."
  docker run --rm \
    --user "$(id -u):$(id -g)" \
    -v "${SCRIPT_DIR}":/workspace \
    -w /workspace \
    "${image}" \
    bash "./${SCRIPT_NAME}"
}

main() {
  local use_docker="false"
  local image="${DEFAULT_IMAGE}"

  while [[ "$#" -gt 0 ]]; do
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
      [[ "$#" -gt 0 ]] || error_exit "--image requires a value"
      image="$1"
      ;;
    *)
      error_exit "Unknown option: $1"
      ;;
    esac
    shift
  done

  if [[ "${use_docker}" = "true" ]]; then
    run_in_docker "${image}"
    return $?
  fi

  command -v unzip >/dev/null 2>&1 || error_exit "unzip not found in PATH"

  cd "${SCRIPT_DIR}"
  mkdir -p "${BACKUP_DIR}"

  local zip_file
  local found=0
  while IFS= read -r -d '' zip_file; do
    found=1
    process_archive "${zip_file}"
  done < <(find . -maxdepth 1 -name "*.zip" -print0)

  [[ "${found}" -eq 1 ]] || warn "No .zip archives found."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
