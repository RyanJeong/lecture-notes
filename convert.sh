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

# TBD
# TARGETS="c cpp"

TARGETS="c"

usage() {
  echo "Usage: ${0} <$(echo ${TARGETS} | tr ' ' '|')>"
}

if [ $# -ne 1 ]; then
  usage
  exit 1
fi

TARGET_DIR=
for target in $TARGETS; do
  if [[ "$target" == "$1" ]]; then
    TARGET_DIR=$1
    break
  fi
done
if [ -z "$TARGET_DIR" ]; then
  usage
  exit 1
fi

# routines:
# 1. run build.sh to get temp.md and its pdf
# 2. convert temp.md to pptx

DIR="$(dirname "$0")"

for file in $(find "$TARGET_DIR" -name README.md | grep -P '\d{2}\/'); do
  CHAPTER=$(basename $(dirname ${file}))
  FILE_NAME="${TARGET_DIR}_${CHAPTER}"

  EXT="pdf"
  echo "Converting ${file} to ${FILE_NAME}.${EXT} ..."

  mkdir -p "${DIR}/${EXT}" &&
    "${DIR}/build.sh" "$file" "$(dirname ${file})/temp.md" "$(dirname ${file})/temp.${EXT}" &&
    cp "$(dirname ${file})/temp.${EXT}" "${DIR}/${EXT}/${FILE_NAME}.${EXT}"
  if [ $? -ne 0 ]; then
    echo "Failed to convert ${file} to ${FILE_NAME}.${EXT}"
    exit 1
  fi

  EXT="pptx"
  echo "Converting ${file} to ${FILE_NAME}.${EXT} ..."

  mkdir -p "${DIR}/${EXT}" &&
    npx marp "$(dirname ${file})/temp.md" -o "$(dirname ${file})/temp.${EXT}" \
      --no-stdin \
      --engine "${DIR}/engine.js" \
      "--${EXT}" \
      --theme "${DIR}/theme.css" \
      --allow-local-files \
      --debug=true &&
    cp "$(dirname ${file})/temp.${EXT}" "${DIR}/${EXT}/${FILE_NAME}.${EXT}"
  if [ $? -ne 0 ]; then
    echo "Failed to convert ${file} to ${FILE_NAME}.${EXT}"
    exit 1
  fi
done

echo "Done."
