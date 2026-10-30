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
#   2. Fenced-code font sizes must be consistent across slides.
#   3. The markdown source must not contain generated empty-file warnings.
#   4. The markdown source must not contain forbidden marker lines.
#
# Examples:
#   ./check_and_release.sh cpp/00/temp.pdf
#   ./check_and_release.sh c/01/temp.pdf
#
# Dependencies:
#   pdfinfo, pdftohtml, pdftoppm (poppler-utils), convert, identify
#   (imagemagick), marp
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

# Script-wide so the EXIT trap can still see it: a variable local to main()
# is already out of scope when the trap fires, and under `set -u` that makes
# the trap itself fail and poison the exit status.
TMP_RENDER_DIR=""

# -- Slide content area check ------------------------------------------------

# Rasterize each page, trim the surrounding whitespace, and compare the trimmed
# height against the full slide height.
check_content_area() {
  local input="$1"
  local tmpdir="$2"
  local pages img page_num trimmed orig_h trim_h ratio percent
  local exceeded=0

  pages=$(pdfinfo "${input}" | awk '/^Pages:/ {print $2}')
  pdftoppm -png "${input}" "${tmpdir}/page"

  for img in "${tmpdir}"/page-*.png; do
    page_num=$(echo "${img}" | grep -oP 'page-\K[0-9]+')
    trimmed="${tmpdir}/trimmed-${page_num}.png"
    convert "${img}" -threshold 90% -trim +repage "${trimmed}"

    orig_h=$(identify -format "%h" "${img}")
    trim_h=$(identify -format "%h" "${trimmed}")
    ratio=$(awk "BEGIN {printf \"%.2f\", ${trim_h}/${orig_h}}")

    if (($(awk "BEGIN {print (${ratio} > ${THRESHOLD})}"))); then
      percent=$(awk "BEGIN {printf \"%d\", ${ratio}*100}")
      warn "Page ${page_num}: content fills ${percent}% of slide (exceeds ${THRESHOLD})"
      exceeded=$((exceeded + 1))
    fi
  done

  if [[ "${exceeded}" -ne 0 ]]; then
    error_exit "${exceeded} out of ${pages} pages exceed the content area threshold."
  fi

  info "All pages are within the acceptable content area."
}

# -- Code font-size check ----------------------------------------------------

check_code_font_size() {
  local input="$1"
  local md_file="$2"
  local tmpdir="$3"
  local code_slides="${tmpdir}/code-slides.txt"
  local font_xml="${tmpdir}/code-fonts.xml"
  local result
  local line

  awk '
    BEGIN { slide = 1 }
    /^[[:space:]]*```/ {
      if (!in_code) {
        language = $0
        sub(/^[[:space:]]*```/, "", language)
        sub(/[[:space:]].*$/, "", language)
        if (language != "" && language != "text") has_code = 1
      }
      in_code = !in_code
      next
    }
    !in_code && /^---[[:space:]]*$/ {
      if (has_code) print slide
      slide++
      has_code = 0
    }
    END {
      if (has_code) print slide
    }
  ' "${md_file}" >"${code_slides}"

  if [[ ! -s "${code_slides}" ]]; then
    info "No fenced-code slides found; skipping code font-size check."
    return 0
  fi

  if ! pdftohtml -xml -stdout "${input}" >"${font_xml}" 2>/dev/null; then
    error "Could not extract font sizes from ${input}."
    return 1
  fi

  if result=$(awk -v code_slide_file="${code_slides}" '
    function attribute(line, name, pattern) {
      pattern = name "=\"[^\"]*\""
      if (match(line, pattern))
        return substr(line, RSTART + length(name) + 2,
                      RLENGTH - length(name) - 3)
      return ""
    }

    FILENAME == code_slide_file {
      code_slides[++slide_count] = $1
      next
    }

    /<page[[:space:]]/ {
      page = attribute($0, "number")
    }

    /<fontspec[[:space:]]/ {
      id = attribute($0, "id")
      size = attribute($0, "size")
      family = tolower(attribute($0, "family"))
      if (family ~ /mono|courier|menlo|consolas|monaco/)
        mono_size[id] = size
    }

    /<text[[:space:]]/ {
      id = attribute($0, "font")
      size = mono_size[id]
      if (size != "")
        font_count[page SUBSEP size]++
    }

    END {
      for (key in font_count) {
        split(key, fields, SUBSEP)
        current_page = fields[1]
        current_size = fields[2]
        count = font_count[key]
        if (count > best_count[current_page] ||
            (count == best_count[current_page] &&
             (best_size[current_page] == "" ||
              current_size + 0 < best_size[current_page] + 0))) {
          best_count[current_page] = count
          best_size[current_page] = current_size
        }
      }

      if (slide_count == 0) {
        print "No fenced-code slides found."
        exit 0
      }

      expected = best_size[code_slides[1]]
      if (expected == "") {
        printf "Slide %s: no monospace code font was detected.\n", code_slides[1]
        mismatch = 1
      }

      for (i = 1; i <= slide_count; i++) {
        current_page = code_slides[i]
        actual = best_size[current_page]
        if (actual == "") {
          printf "Slide %s: no monospace code font was detected.\n", current_page
          mismatch = 1
        } else if (expected != "" && actual != expected) {
          printf "Slide %s: code font is %s pt; expected %s pt.\n",
            current_page, actual, expected
          mismatch = 1
        }
      }

      if (mismatch) exit 1
      printf "Code font size is consistent at %s pt across %d slides.\n",
        expected, slide_count
    }
  ' "${code_slides}" "${font_xml}"); then
    info "${result}"
    return 0
  fi

  while IFS= read -r line; do
    error "${line}"
  done <<<"${result}"
  return 1
}

# -- Forbidden pattern check -------------------------------------------------

check_forbidden_patterns() {
  local md_file="$1"
  local content_errors=0

  [[ -f "${md_file}" ]] || error_exit "Markdown source not found: ${md_file}"

  if grep -nP '// Warning: File .+ not found; creating empty file\.' "${md_file}"; then
    error "${md_file} contains a generated empty-file warning comment."
    content_errors=$((content_errors + 1))
  fi

  if grep -nF 'DO NOT CONTAIN THIS LINE IN THE MARKDOWN' "${md_file}"; then
    error "${md_file} contains a forbidden marker line."
    content_errors=$((content_errors + 1))
  fi

  if [[ "${content_errors}" -gt 0 ]]; then
    error_exit "${content_errors} forbidden pattern(s) found in ${md_file}. Release aborted."
  fi

  info "Content checks passed."
}

# -- Release -----------------------------------------------------------------

release_chapter() {
  local input="$1"
  local input_dir="$2"
  local lang="$3"
  local ch="$4"
  local md_file="$5"

  mkdir -p "release/${lang}"
  cp "${input}" "release/${lang}/${ch}.pdf"
  info "Copied ${lang}/${ch}.pdf"

  marp --pptx --allow-local-files --theme ./theme.css "${md_file}"
  mv "${input_dir}/temp.pptx" "release/${lang}/${ch}.pptx"
  info "Generated ${lang}/${ch}.pptx"

  info "Release completed for ${lang}/${ch}."
}

main() {
  case "${1:-}" in
  -h | --help)
    show_help
    exit 0
    ;;
  esac

  local input="${1:-}"
  [[ -n "${input}" ]] || error_exit "Usage: ${SCRIPT_NAME} <input.pdf>"
  [[ -f "${input}" ]] || error_exit "File not found: ${input}"

  # input: cpp/00/temp.pdf -> release/cpp/00.pdf
  local input_dir lang ch md_file
  input_dir=$(dirname "${input}") # cpp/00
  lang=$(dirname "${input_dir}")  # cpp
  ch=$(basename "${input_dir}")   # 00
  md_file="${input_dir}/temp.md"

  TMP_RENDER_DIR=$(mktemp -d)
  trap '[ -n "${TMP_RENDER_DIR}" ] && rm -rf "${TMP_RENDER_DIR}"' EXIT INT TERM

  check_content_area "${input}" "${TMP_RENDER_DIR}"
  if ! check_code_font_size "${input}" "${md_file}" "${TMP_RENDER_DIR}"; then
    error_exit "Code font-size check failed. Release aborted."
  fi
  check_forbidden_patterns "${md_file}"
  release_chapter "${input}" "${input_dir}" "${lang}" "${ch}" "${md_file}"
}

if [ "${BASH_SOURCE[0]}" = "$0" ]; then
  main "$@"
fi
