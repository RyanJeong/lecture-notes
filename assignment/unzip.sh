#!/bin/bash

backup_dir=$(dirname $0)/backup
mkdir -p "$backup_dir"
exit
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

  # 3. Ignore whitespaces of directory name
  for name in *; do
    if [[ "$name" == *" "* ]]; then
      new_name="${name// /_}"
      mv "$name" "$new_name"
    fi
  done

  # 4. print not c or cpp extension files
  result="results.txt"
  > "$PWD"/"$result"
  find . -type f ! \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.cxx" -name "*.h" -name "*.hpp" \) \
      | while IFS= read -r file; do
    if [[ "$file" == "./${result}" ]]; then
      continue
    fi

    # .zip file
    if [[ "$file" == *.zip ]]; then
      if ! unzip "$file" -d "${file%/*}" >/dev/null; then
        echo ">>>> ${file}" >> "$PWD"/"$result"
      fi
    else
      echo ">>>> ${file}" >> "$PWD"/"$result"
    fi
  done
  sudo chown -R "$USER":"$USER" ./
  sudo chmod -R u+rwX ./
  popd >/dev/null

  echo "-> Successfully filtered unnecessary files"

  cp -r "$target_dir" "$backup_dir"

  echo "-> Successfully backup to $backup_dir"
done
