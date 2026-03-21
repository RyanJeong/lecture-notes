#!/usr/bin/env bash

# ============================================================================
# Check and Release
# ============================================================================
# Usage:
#   ./check_and_release.sh <input.pdf>
#
# Description:
#   Validates slide content area and forbidden patterns, then releases
#   PDF and PPTX to the release directory.
#
# Checks:
#   1. Each slide's content must not exceed the height threshold (77%).
#   2. The markdown source must not contain generated empty-file warnings.
#   3. The markdown source must not contain forbidden marker lines.
#
# Examples:
#   ./check_and_release.sh cpp/00/temp.pdf
#   ./check_and_release.sh c/01/temp.pdf
#
# Dependencies:
#   pdfinfo, pdftoppm (poppler-utils), convert, identify (imagemagick), marp
#
# ============================================================================

set -euo pipefail

# Color output functions (compatible with macOS and Linux)
color_red() { printf '\033[31m'; }
color_green() { printf '\033[32m'; }
color_yellow() { printf '\033[33m'; }
color_reset() { printf '\033[0m'; }

info() { printf '%s\n' "$(color_green)[INFO]$(color_reset) ${1:-}"; }
warn() { printf '%s\n' "$(color_yellow)[WARN]$(color_reset) ${1:-}"; }
error() { printf '%s\n' "$(color_red)[ERROR]$(color_reset) ${1:-}" >&2; }

readonly SCRIPT_NAME="$(basename "$0")"

show_help() {
  awk '/^# =====/{delim++; if(delim==3) exit; next} delim==2 && /^# /{sub(/^# /, ""); print}' "$0"
}

error_exit() {
  error "$1"
  exit "${2:-1}"
}

readonly THRESHOLD=0.77 # 77%

# -- Argument parsing --------------------------------------------------------

if [[ "${1:-}" == "-h" ]] || [[ "${1:-}" == "--help" ]]; then
  show_help
  exit 0
fi

input="${1:-}"
[[ -n "$input" ]] || error_exit "Usage: $SCRIPT_NAME <input.pdf>"
[[ -f "$input" ]] || error_exit "File not found: $input"

# -- Slide content area check ------------------------------------------------

pages=$(pdfinfo "$input" | awk '/^Pages:/ {print $2}')

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

pdftoppm -png "$input" "$tmpdir/page"

exceeded_pages=0
for img in "$tmpdir"/page-*.png; do
  page_num=$(echo "$img" | grep -oP 'page-\K[0-9]+')
  trimmed="$tmpdir/trimmed-$page_num.png"
  convert "$img" -threshold 90% -trim +repage "$trimmed"

  orig_h=$(identify -format "%h" "$img")
  trim_h=$(identify -format "%h" "$trimmed")
  ratio=$(awk "BEGIN {printf \"%.2f\", $trim_h/$orig_h}")

  if (($(awk "BEGIN {print ($ratio > $THRESHOLD)}"))); then
    local_percent=$(awk "BEGIN {printf \"%d\", $ratio*100}")
    warn "Page $page_num: content fills ${local_percent}% of slide (exceeds ${THRESHOLD})"
    exceeded_pages=$((exceeded_pages + 1))
  fi
done

if [[ "$exceeded_pages" -ne 0 ]]; then
  error_exit "$exceeded_pages out of $pages pages exceed the content area threshold."
fi

info "All pages are within the acceptable content area."

# -- Forbidden pattern check -------------------------------------------------

# input: cpp/00/temp.pdf -> release/cpp/00.pdf
input_dir=$(dirname "$input") # cpp/00
lang=$(dirname "$input_dir")  # cpp
ch=$(basename "$input_dir")   # 00
md_file="${input_dir}/temp.md"

[[ -f "$md_file" ]] || error_exit "Markdown source not found: $md_file"

content_errors=0

if grep -nP '// Warning: File .+ not found; creating empty file\.' "$md_file"; then
  error "$md_file contains a generated empty-file warning comment."
  content_errors=$((content_errors + 1))
fi

if grep -nF 'DO NOT CONTAIN THIS LINE IN THE MARKDOWN' "$md_file"; then
  error "$md_file contains a forbidden marker line."
  content_errors=$((content_errors + 1))
fi

if [[ "$content_errors" -gt 0 ]]; then
  error_exit "$content_errors forbidden pattern(s) found in $md_file. Release aborted."
fi

info "Content checks passed."

# -- Release -----------------------------------------------------------------

mkdir -p "release/${lang}"
cp "$input" "release/${lang}/${ch}.pdf"
info "Copied ${lang}/${ch}.pdf"

marp --pptx --allow-local-files --theme ./theme.css "$md_file"
mv "${input_dir}/temp.pptx" "release/${lang}/${ch}.pptx"
info "Generated ${lang}/${ch}.pptx"

info "Release completed for ${lang}/${ch}."
