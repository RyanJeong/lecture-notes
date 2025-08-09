#!/bin/bash

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

process_file() {
  info "Processing ${SRC_MD}..."

  # Clear the temporary file
  >"$TMP_MD"

  # Read the source markdown file line by line
  while IFS= read -r line; do
    # Check for Markdown placeholder: [//]: # (INCLUDE: filename)
    if echo "$line" | grep -qE '^\[\/\/\]:\s*#\s*\(INCLUDE:\s*[^)]+\)'; then
      # Extract filename using sed; assumes no closing parenthesis inside filename
      filename=$(echo "$line" | sed -E 's/^\[\/\/\]:\s*#\s*\(INCLUDE:\s*([^)]*)\).*/\1/')

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

      # Write the fenced code block start (with language hint if available)
      echo '```'"${lang}" >>"$TMP_MD"
      # Append the content of the file (if exists); if not, create an empty file using touch.
      if [ -f "$filename" ]; then
        cat "$filename" >>"$TMP_MD"

        # Check whether the last character is a newline
        if [ -n "$(tail -c1 "$filename" | tr -d '\n')" ]; then
          # Last character is NOT a newline → add one
          echo >>"$TMP_MD"
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
  done <"$SRC_MD"

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
