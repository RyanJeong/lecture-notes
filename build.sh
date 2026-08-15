#!/usr/bin/env bash

# ============================================================================
# build.sh
# ============================================================================
# Usage:
#   ./build.sh SOURCE_MARKDOWN TEMP_MARKDOWN OUTPUT [loop]
#
# Description:
#   Build a PDF/PPTX slide deck from a chapter README.md, expanding external
#   code placeholders, syntax-checking the included sources, and invoking
#   marp-cli for the conversion.
#
#   The placeholder syntax is Markdown-compatible:
#     [//]: # (INCLUDE: filename [--from N] [--to M] [--no-comment] [--reference])
#
# Arguments:
#   SOURCE_MARKDOWN   Chapter source, laid out as <course>/<NN>/README.md
#   TEMP_MARKDOWN     Generated markdown with code blocks expanded
#   OUTPUT            Output file; the extension selects the marp format
#   loop              Optional; reprocess every second until interrupted
#
# Options:
#   -h, --help   Show this help message
#
# Examples:
#   ./build.sh c/01/README.md c/01/temp.md c/01/temp.pdf
#   ./build.sh c/01/README.md c/01/temp.md c/01/temp.pdf loop
#
# ============================================================================

set -euo pipefail

color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_cyan() { printf '\033[36m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }
debug() { printf '%s\n' "$(color_cyan)[DEBUG]$(color_reset) ${1:-}"; }

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly SCRIPT_NAME="$(basename "$0")"

# Script-wide state shared with process_file(); assigned once in main().
SRC_MD="" # Source Markdown file (with placeholders)
TMP_MD="" # Temporary Markdown file with included code
OUTPUT="" # Output file
LOOP_MODE="false"
SYNTAX_LANG="" # Course directory owning the syntax checker
SYNTAX_TMP=""  # Temp dir for syntax checking; cleaned up on any exit

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

# Determine the course directory from the source path, which is laid out as
#   <course>/<NN>/README.md
# so the course owning this chapter is the parent of the chapter directory.
# Resolving to an absolute path first handles both relative invocations and the
# absolute path the editor's Run-on-Save hook passes. Adding a new course
# therefore requires no change here: its own check_syntax.sh is picked up.
resolve_syntax_lang() {
  local chapter_dir

  if [[ -d "$(dirname "${SRC_MD}")" ]]; then
    chapter_dir="$(cd "$(dirname "${SRC_MD}")" && pwd)"
    SYNTAX_LANG="$(basename "$(dirname "${chapter_dir}")")"
  fi

  if [[ -z "${SYNTAX_LANG}" ]] || [[ ! -x "${SYNTAX_LANG}/check_syntax.sh" ]]; then
    warn "No check_syntax.sh for course '${SYNTAX_LANG:-?}'; skipping syntax check."
    SYNTAX_LANG=""
  fi
}

process_file() {
  # Create a fresh temp directory for syntax checking (cleaned up by EXIT trap).
  [ -n "${SYNTAX_TMP}" ] && rm -rf "${SYNTAX_TMP}"
  SYNTAX_TMP=$(mktemp -d "${SYNTAX_LANG:-.}/tmp_syntax_XXXXXX")
  mkdir -p "${SYNTAX_TMP}/src"

  info "Processing ${SRC_MD}..."

  # Clear the temporary file
  >"$TMP_MD"

  # Read the source markdown file line by line
  while IFS= read -r line; do
    # Check for Markdown placeholder: [//]: # (INCLUDE: filename)
    if echo "$line" | grep -qE '^\[\/\/\]:[[:space:]]*#[[:space:]]*\(INCLUDE:'; then
      # Extract the full argument string inside the parentheses
      args=$(echo "$line" | sed -E 's/^\[\/\/\]:[[:space:]]*#[[:space:]]*\((INCLUDE:.*)\).*/\1/')
      # Split the argument string into an array
      read -ra tokens <<<"$args"

      # Initialize variables
      filename=""
      range_from=()
      range_to=()
      no_comment="false"
      reference="false"
      _cur_from=""
      _num_from_args=0
      _num_to_args=0

      # Parse tokens sequentially, building ordered (from, to) range pairs.
      # --to N before any --from  -> range [1, N]
      # --from N then --to M      -> range [N, M]
      # --from N then --from M    -> finalize [N, end], open new range at M
      # trailing --from N         -> range [N, end]
      for ((i = 0; i < ${#tokens[@]}; i++)); do
        token="${tokens[$i]}"
        case "$token" in
        INCLUDE:)
          filename="${tokens[$((i + 1))]}"
          ;;
        --from)
          # Finalize any previously open --from as [from, end]
          if [ -n "$_cur_from" ]; then
            range_from+=("$_cur_from")
            range_to+=("")
          fi
          _cur_from="${tokens[$((i + 1))]}"
          _num_from_args=$((_num_from_args + 1))
          ;;
        --to)
          # Finalize current range [cur_from_or_1, to]
          range_from+=("${_cur_from:-1}")
          range_to+=("${tokens[$((i + 1))]}")
          _cur_from=""
          _num_to_args=$((_num_to_args + 1))
          ;;
        --no-comment)
          no_comment="true"
          ;;
        --reference)
          reference="true"
          ;;
        esac
      done
      # Finalize any unclosed --from
      if [ -n "$_cur_from" ]; then
        range_from+=("$_cur_from")
        range_to+=("")
      fi

      # Determine language based on file extension
      ext="${filename##*.}"
      lang=""
      case "$ext" in
      c | h | i) lang="c" ;;
      cpp | cc | cxx | hpp) lang="cpp" ;;
      py) lang="python" ;;
      sh) lang="bash" ;;
      java) lang="java" ;;
      js) lang="javascript" ;;
      *) lang="" ;; # No language specified
      esac

      info "Including file: ${filename} (language: ${lang})"

      # Compute syntax-check destination mirroring the path after the first src/ segment.
      # e.g. ./c/04/src/02_atof.c          -> SYNTAX_TMP/02_atof.c
      #      ./c/04/src/rudimentary_calc/main.c -> SYNTAX_TMP/rudimentary_calc/main.c
      local syntax_dest
      local rel_to_src
      rel_to_src="${filename#*src/}"
      syntax_dest="${SYNTAX_TMP}/src/${rel_to_src}"

      # Stage a VERBATIM copy for the syntax check -- never the slide version.
      # The markdown copy is range-sliced and has its "DO NOT CONTAIN" guard
      # lines stripped; compiling that would report bogus diagnostics for code
      # a range omitted, and would compile bodies the author deliberately
      # fenced off with "#if 0 /* DO NOT CONTAIN ... */" (intentionally broken
      # teaching examples). Copying the original keeps the staged tree a
      # faithful subset of src/, so it compiles exactly as check_syntax.sh does.
      # Only source files are staged. A Makefile shown on a slide would
      # otherwise be built in this partial tree and fail on the .c files no
      # slide happens to include; the real projects are built by check_syntax.sh.
      if [ -f "${filename}" ] && [ -n "${lang}" ]; then
        mkdir -p "$(dirname "${syntax_dest}")"
        cp "${filename}" "${syntax_dest}"
      elif [ "${reference}" = "true" ] && [ ! -f "${filename}" ]; then
        warn "Reference file not found: ${filename}"
      fi

      # --reference: stage only, do not add a code block to markdown.
      if [ "${reference}" = "true" ]; then
        [ -f "${filename}" ] && info "Reference file staged: ${syntax_dest}"
        continue
      fi

      # Write the fenced code block start (with language hint if available)
      echo '```'"${lang}" >>"$TMP_MD"
      # Append the content of the file (if exists); if not, create an empty file using touch.
      if [ -f "$filename" ]; then
        num_ranges=${#range_from[@]}

        # Slide-continuation comments (when --no-comment is not set and ranges exist):
        #   _num_from_args == _num_to_args : both top and bottom comments
        #   _num_from_args  > _num_to_args : top comment only  ("continued from previous slide")
        #   _num_from_args  < _num_to_args : bottom comment only ("continues on next slide")
        if [ "$no_comment" = "false" ] && [ "$num_ranges" -gt 0 ]; then
          if [ "$_num_from_args" -ge "$_num_to_args" ]; then
            echo "/* continued from previous slide */" >>"$TMP_MD"
          fi
        fi

        # Extract and append content to the markdown only; the syntax-check
        # copy was already staged verbatim above.
        if [ "${num_ranges}" -eq 0 ]; then
          # No --from/--to: whole file, strip DO NOT CONTAIN lines.
          sed -n "1,\$p" "${filename}" |
            grep -v "DO NOT CONTAIN THIS LINE IN THE MARKDOWN" |
            tr -d '\r' |
            awk 'NF{found=NR} {lines[NR]=$0} END{for(i=1;i<=found;i++) print lines[i]}' \
              >>"${TMP_MD}"
        else
          # One or more ranges: concatenate in order, no DO NOT CONTAIN stripping.
          {
            for ((r = 0; r < num_ranges; r++)); do
              f="${range_from[$r]}"
              t="${range_to[$r]}"
              if [ -n "${t}" ]; then
                sed -n "${f},${t}p" "${filename}"
              else
                sed -n "${f},\$p" "${filename}"
              fi
            done
          } | tr -d '\r' |
            awk 'NF{found=NR} {lines[NR]=$0} END{for(i=1;i<=found;i++) print lines[i]}' \
              >>"${TMP_MD}"
        fi

        if [ "$no_comment" = "false" ] && [ "$num_ranges" -gt 0 ]; then
          if [ "$_num_to_args" -ge "$_num_from_args" ]; then
            echo "/* continues on next slide */" >>"$TMP_MD"
          fi
        fi
      else
        echo "// Warning: File ${filename} not found; creating empty file." >>"$TMP_MD"
        touch "$filename"
      fi
      # Write the fenced code block end
      echo '```' >>"$TMP_MD"
    else
      # Otherwise, simply copy the line
      echo "$line" >>"$TMP_MD"
    fi
  done <"${SRC_MD}"

  # Run syntax check on all collected source files before building.
  if [ -n "${SYNTAX_LANG}" ]; then
    local syntax_tmp_name
    syntax_tmp_name="$(basename "${SYNTAX_TMP}")"
    info "Running syntax check on collected files..."
    if ! "${SYNTAX_LANG}/check_syntax.sh" "${syntax_tmp_name}"; then
      error "Syntax check failed. Fix the errors above before building."
      exit 1
    fi
  fi

  TYPE="${OUTPUT##*.}"
  info "Converting to ${TYPE}..."

  npx marp "$TMP_MD" \
    --no-stdin \
    --engine engine.js \
    "--${TYPE}" \
    --theme theme.css \
    --allow-local-files \
    -o "$OUTPUT" \
    --debug=true

  info "Conversion complete: ${OUTPUT}"
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  if [[ "$#" -lt 3 ]]; then
    error "Usage: ${SCRIPT_NAME} SOURCE_MARKDOWN TEMP_MARKDOWN OUTPUT [loop]"
    show_help
    exit 1
  fi

  # Relative arguments are resolved against the repository root.
  cd "${SCRIPT_DIR}"

  SRC_MD="$1"
  TMP_MD="$2"
  OUTPUT="$3"

  if [[ "$#" -eq 4 ]] && [[ "$4" = "loop" ]]; then
    LOOP_MODE="true"
  fi

  [[ -f "${SRC_MD}" ]] || error_exit "Source markdown not found: ${SRC_MD}"

  resolve_syntax_lang

  # Clean up the syntax-check temp dir on any exit path.
  trap '[ -n "${SYNTAX_TMP}" ] && rm -rf "${SYNTAX_TMP}"' EXIT INT TERM

  if [[ "${LOOP_MODE}" = "true" ]]; then
    # Infinite loop for real-time processing
    while true; do
      process_file
      # Sleep for 1 second before next processing cycle
      sleep 1
    done
  else
    process_file
  fi
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
