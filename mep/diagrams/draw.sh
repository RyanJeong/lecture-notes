#!/usr/bin/env bash

# ============================================================================
# Draw MEP Lab Diagrams
# ============================================================================
# Usage:
#   ./diagrams/draw.sh [OPTIONS] [TARGET...]
#
# Description:
#   Regenerates the lab circuit diagrams straight into each chapter's img/
#   directory. Schemdraw produces the symbol-level schematics, WireViz the
#   pin-level wiring diagrams. Everything runs inside a container so the
#   Graphviz dependency never has to be installed on the host.
#
# Arguments:
#   TARGET   Keys to redraw (e.g. lab01 pinout). Defaults to all of them.
#
# Options:
#   -h, --help     Show this help message
#   -l, --list     List the keys and the files each one writes
#   -w, --wiring   Also rebuild the WireViz pin-to-pin diagrams. These are
#                  not used by the slides; they land in diagrams/wiring/out/
#
# Dependencies:
#   docker
# ============================================================================

set -euo pipefail

color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly SCRIPT_NAME="$(basename "$0")"
readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly COURSE_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
readonly DOCKER_IMAGE="mep-diagrams"

# One row per drawing: key|kind|module|chapter|output basename.
# Kinds: schematic (Schemdraw), layout (breadboard), wiring (WireViz).
# Every Python generator writes its own OUT_PATH; the basename here is what
# gets reported and, for WireViz, what the file is named.
readonly ITEMS=(
  "pinout|schematic|rpi_pinout|09|22-rpi-pinout"
  "lab01|schematic|lab01_led_button|09|04-lab01-circuit"
  "lab01|layout|lab01_led_button|09|20-lab01-layout"
  "lab01|wiring|lab01_led_button|09|20-lab01-wiring"
  "lab02|schematic|lab02_sequence|09|08-lab02-circuit"
  "lab02|layout|lab02_sequence|09|21-lab02-layout"
  "lab02|wiring|lab02_sequence|09|21-lab02-wiring"
  "lab03|schematic|lab03_dht11|10|09-lab03-circuit"
  "lab03|layout|lab03_dht11|10|16-lab03-layout"
  "lab03|wiring|lab03_dht11|10|16-lab03-wiring"
  "lab04|schematic|lab04_cds_mcp3008|10|11-lab04-divider-circuit"
  "lab04|layout|lab04_cds_mcp3008|10|17-lab04-layout"
  "lab04|wiring|lab04_cds_mcp3008|10|17-lab04-wiring"
  "lab05|schematic|lab05_hcsr04|10|14-lab05-circuit"
  "lab05|layout|lab05_hcsr04|10|18-lab05-layout"
  "lab05|wiring|lab05_hcsr04|10|18-lab05-wiring"
)
readonly WIRING_OUT="diagrams/wiring/out"
WITH_WIRING="false"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

list_targets() {
  local row key kind chapter name dest
  for row in "${ITEMS[@]}"; do
    IFS='|' read -r key kind _ chapter name <<<"${row}"
    if [ "${kind}" = "wiring" ]; then
      dest="${WIRING_OUT}/${name}.png"
    else
      dest="${chapter}/img/${name}.png"
    fi
    printf '  %-7s %-10s %s\n' "${key}" "${kind}" "${dest}"
  done
}

require_docker() {
  command -v docker >/dev/null 2>&1 || {
    error "docker not found in PATH"
    return 1
  }
  docker info >/dev/null 2>&1 || {
    error "docker daemon is not running"
    return 1
  }
}

build_image() {
  if docker image inspect "${DOCKER_IMAGE}" >/dev/null 2>&1; then
    return 0
  fi
  info "Building ${DOCKER_IMAGE} (first run only)"
  docker build -q -t "${DOCKER_IMAGE}" "${SCRIPT_DIR}" >/dev/null
}

run_container() {
  docker run --rm \
    -v "${COURSE_DIR}:/workspace" \
    -w /workspace \
    -e PYTHONPATH=/workspace/diagrams \
    "${DOCKER_IMAGE}" "$@"
}

draw_item() {
  local kind="$1" module="$2" chapter="$3" name="$4"
  case "${kind}" in
    schematic)
      run_container python "diagrams/schematic/${module}.py" >/dev/null || return 1
      info "  ${chapter}/img/${name}.png"
      ;;
    layout)
      run_container python "diagrams/layout/${module}.py" >/dev/null || return 1
      info "  ${chapter}/img/${name}.png"
      ;;
    wiring)
      run_container wireviz -f p -o "${WIRING_OUT}" -O "${name}" \
        "diagrams/wiring/${module}.yml" >/dev/null || return 1
      info "  ${WIRING_OUT}/${name}.png"
      ;;
    *)
      error "unknown kind '${kind}'"
      return 1
      ;;
  esac
}

draw_target() {
  local key="$1"
  local row name kind module chapter output found="false"
  for row in "${ITEMS[@]}"; do
    IFS='|' read -r name kind module chapter output <<<"${row}"
    [ "${name}" = "${key}" ] || continue
    [ "${kind}" != "wiring" ] || [ "${WITH_WIRING}" = "true" ] || continue
    if [ "${found}" = "false" ]; then
      info "${key}:"
      found="true"
    fi
    draw_item "${kind}" "${module}" "${chapter}" "${output}" || return 1
  done
  if [ "${found}" = "false" ]; then
    error "unknown target '${key}' (try '${SCRIPT_NAME} --list')"
    return 1
  fi
}

collect_targets() {
  local row key
  for row in "${ITEMS[@]}"; do
    IFS='|' read -r key _ <<<"${row}"
    printf '%s\n' "${key}"
  done | awk '!seen[$0]++'
}

main() {
  local -a targets=()
  while [ $# -gt 0 ]; do
    case "$1" in
      -h | --help)
        show_help
        return 0
        ;;
      -l | --list)
        list_targets
        return 0
        ;;
      -w | --wiring)
        WITH_WIRING="true"
        ;;
      -*)
        error "unknown option: $1"
        return 1
        ;;
      *)
        targets+=("$1")
        ;;
    esac
    shift
  done

  if [ "${#targets[@]}" -eq 0 ]; then
    while IFS= read -r line; do targets+=("${line}"); done < <(collect_targets)
  fi

  require_docker
  build_image

  local failed=0 target
  for target in "${targets[@]}"; do
    draw_target "${target}" || failed=$((failed + 1))
  done

  if [ "${failed}" -gt 0 ]; then
    error "${failed} target(s) failed."
    return 1
  fi
  info "All diagrams written."
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
