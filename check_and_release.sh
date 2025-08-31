#!/bin/bash

# Usage: ./check_and_release.sh input.pdf

set -Eeuo pipefail

input="$1"
if [ -z "$input" ]; then
  echo "Usage: $0 input.pdf"
  exit 1
fi

threshold=0.77 # 77%

# Get total pages
pages=$(pdfinfo "$input" | awk '/^Pages:/ {print $2}')

# Create temp dir for images
tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

# Convert each page to PNG image
pdftoppm -png "$input" "$tmpdir/page"

# For each page, check content area
exceeded_pages=0
for img in "$tmpdir"/page-*.png; do
  page_num=$(echo "$img" | grep -oP 'page-\K[0-9]+')
  # Convert to black and white, then trim whitespace
  trimmed="$tmpdir/trimmed-$page_num.png"
  convert "$img" -threshold 90% -trim +repage "$trimmed"
  # Get original and trimmed heights
  orig_h=$(identify -format "%h" "$img")
  trim_h=$(identify -format "%h" "$trimmed")
  # Calculate content ratio
  ratio=$(awk "BEGIN {printf \"%.2f\", $trim_h/$orig_h}")
  # If content exceeds threshold, print page number
  if (($(awk "BEGIN {print ($ratio > $threshold)}"))); then
    percent=$(awk "BEGIN {printf \"%d\", $ratio*100}")
    echo "Page $page_num: content fills $percent% of slide (exceeds ${threshold})"
    exceeded_pages=$((exceeded_pages + 1))
  fi
done

if [ "$exceeded_pages" -eq 0 ]; then
  echo "All pages are within the acceptable content area."

  # input: cpp/00/temp.pdf -> output: cpp_00.pdf
  dirname=$(dirname "$input") # cpp/00
  lang=$(dirname "$dirname")  # cpp
  ch=$(basename "$dirname")   # 00

  mkdir -p "release/${lang}"
  cp "$input" "release/${lang}/${ch}.pdf"

  marp --pptx --allow-local-files --theme ./theme.css "${dirname}/temp.md"
  mv "${dirname}/temp.pptx" "release/${lang}/${ch}.pptx"
else
  echo "$exceeded_pages out of $pages pages exceed the content area threshold."
fi
