#!/usr/bin/env bash

set -euo pipefail

# Color functions (using printf)
color_red() { printf "\033[31m%s\033[0m" "$1"; }
color_green() { printf "\033[32m%s\033[0m" "$1"; }
color_yellow() { printf "\033[33m%s\033[0m" "$1"; }
color_blue() { printf "\033[34m%s\033[0m" "$1"; }
color_magenta() { printf "\033[35m%s\033[0m" "$1"; }
color_cyan() { printf "\033[36m%s\033[0m" "$1"; }
color_bold() { printf "\033[1m%s\033[0m" "$1"; }

# Logging functions
info() { printf "%s %s\n" "$(color_green "[$(basename "$0")][INFO]")" "$1"; }
warn() { printf "%s %s\n" "$(color_yellow "[$(basename "$0")][WARN]")" "$1"; }
error() { printf "%s %s\n" "$(color_red "[$(basename "$0")][ERROR]")" "$1"; }
debug() { printf "%s %s\n" "$(color_cyan "[$(basename "$0")][DEBUG]")" "$1"; }

# Change working directory to the directory of the script.
cd "$(dirname "$0")"

# build.sh: Build PDF/PPTX from Markdown with external code inclusion.
# USAGE: ./build.sh source_markdown temp_markdown output_pdf [loop]
# If "loop" is passed as the fourth argument, the script runs continuously.
# Otherwise, it processes the file once.
# This script watches the source Markdown file for changes and replaces
# placeholders with code blocks before invoking marp-cli for PDF/PPTX conversion.
# The placeholder syntax used is Markdown-compatible:
# [//]: # (INCLUDE: filename)

if [ "$#" -lt 3 ]; then
  info "Usage: $0 source_markdown temp_markdown output_pdf [loop]"
  exit 1
fi

SRC_MD="$1" # Source Markdown file (with placeholders)
TMP_MD="$2" # Temporary Markdown file with included code
OUTPUT="$3" # Output file
LOOP_MODE="false"

# Check if a fourth argument "loop" is passed.
if [ "$#" -eq 4 ] && [ "$4" = "loop" ]; then
  LOOP_MODE="true"
fi

# Global temp dir for syntax checking; cleaned up on any exit.
SYNTAX_TMP=""
trap '[ -n "${SYNTAX_TMP}" ] && rm -rf "${SYNTAX_TMP}"' EXIT INT TERM

process_file() {
  # Create a fresh temp directory for syntax checking (cleaned up by EXIT trap).
  [ -n "${SYNTAX_TMP}" ] && rm -rf "${SYNTAX_TMP}"
  SYNTAX_TMP=$(mktemp -d "c/tmp_syntax_XXXXXX")
  mkdir -p "${SYNTAX_TMP}/src"

  info "Processing ${SRC_MD}..."

  # Clear the temporary file
  >"$TMP_MD"

  # Read the source markdown file line by line
  while IFS= read -r line; do
    # Check for Markdown placeholder: [//]: # (INCLUDE: filename)
    if echo "$line" | grep -qE '^\[\/\/\]:\s*#\s*\(INCLUDE:'; then
      # Extract the full argument string inside the parentheses
      args=$(echo "$line" | sed -E 's/^\[\/\/\]:\s*#\s*\((INCLUDE:.*)\).*/\1/')
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
      if [ "${no_comment}" = "false" ] || [ "${reference}" = "true" ]; then
        syntax_dest="${SYNTAX_TMP}/${rel_to_src}"
        mkdir -p "$(dirname "${syntax_dest}")"
      else
        syntax_dest="/dev/null"
      fi

      # --reference: copy only to syntax_dest, do not add a code block to markdown.
      if [ "${reference}" = "true" ]; then
        if [ -f "${filename}" ]; then
          cp "${filename}" "${syntax_dest}"
          info "Reference file staged: ${syntax_dest}"
        else
          warn "Reference file not found: ${filename}"
        fi
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

        # Extract and append content.
        # The same filtered output goes to both TMP_MD (markdown) and syntax_dest (syntax check).
        if [ "${num_ranges}" -eq 0 ]; then
          # No --from/--to: whole file, strip DO NOT CONTAIN lines.
          sed -n "1,\$p" "${filename}" |
            grep -v "DO NOT CONTAIN THIS LINE IN THE MARKDOWN" |
            tr -d '\r' |
            awk 'NF{found=NR} {lines[NR]=$0} END{for(i=1;i<=found;i++) print lines[i]}' |
            tee -a "${syntax_dest}" \
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
            awk 'NF{found=NR} {lines[NR]=$0} END{for(i=1;i<=found;i++) print lines[i]}' |
            tee -a "${syntax_dest}" \
              >>"${TMP_MD}"
        fi

        # Print current accumulated content of the syntax-check file after each INCLUDE write.
        if [ "${syntax_dest}" != "/dev/null" ] && [ -s "${syntax_dest}" ]; then
          info "Syntax-check content for: $(basename "${filename}")"
          cat "${syntax_dest}"
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
  local syntax_tmp_name
  syntax_tmp_name="$(basename "${SYNTAX_TMP}")"
  info "Running syntax check on collected files..."
  if ! c/check_syntax.sh "${syntax_tmp_name}"; then
    error "Syntax check failed. Fix the errors above before building."
    exit 1
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

if [ "$LOOP_MODE" = "true" ]; then
  # Infinite loop for real-time processing
  while true; do
    process_file
    # Sleep for 1 second before next processing cycle
    sleep 1
  done
else
  process_file
fi
