#!/bin/bash

# Munseong: After generating files, run ../clean.sh and remove it if it works well
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

DIR=$(dirname $0)
debug $DIR

info "Clean generated files ..."
for file in $(find "$DIR" -type f \( -name "temp.pdf" -o -name "temp.md" -o -name "temp.pptx" -o -name "a.out" -o ! -name "*.*" \)); do
  info "Removing $file ..."
  rm $file
done

info "Clean unnecessary image files ..."
for dir in $(find $DIR -mindepth 1 -maxdepth 1 -type d); do
  cd $dir
  mapfile -t FS_IMGS < <(find . -regextype posix-extended -iregex '.*\.(png|jpe?g|gif|bmp|webp|svg)' |
    sed 's|^\./||' |
    sort)
  echo "Filesystem : ${FS_IMGS[@]}"
  echo
  mapfile -t README_IMGS < <(grep -E '^!\[' README.md 2>/dev/null |
    sed -n 's/.*(\([^)]*\)).*/\1/p' |
    sort)
  echo "README.md  : ${README_IMGS[@]}"
  echo

  for img in "${FS_IMGS[@]}"; do
    skip=false
    for used in "${README_IMGS[@]}"; do
      if [[ "$img" == "$used" ]]; then
        skip=true
        break
      fi
    done
    $skip || (info "$img will be removed ..." && rm -rf $img)
  done
  cd ../
done
