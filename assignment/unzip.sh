#!/bin/bash

find . -name "*.zip" | while IFS= read -r zip_file; do
  echo "Processing: $zip_file"

  base_name=$(basename "$zip_file" .zip)
  target_dir=$(echo "$base_name" | grep -oE '[0-9]+' | paste -sd '_')
  mkdir -p "$target_dir"
  unzip -q "$zip_file" -d "$target_dir"

  echo "-> Extracted to: $target_dir"

  pushd "$target_dir" >/dev/null

  # 1. *online*
  rm -rf *online*

  # 2. hidden files (prefix with `.`)
  find . -name ".*" | while IFS= read -r file; do
    if [[ "$file" == "." ]]; then
      continue
    fi

    rm -rf "$file"
  done

  # 3. print not c extension files
  find . -type f ! -name "*.c" | while IFS= read -r file; do
    echo ">>>> ${file}"
  done
  popd >/dev/null

  echo "-> Successfully filtered unnecessary files"
done

