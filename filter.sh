#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 <PATH>"
  exit 1
fi

target_dir="$1"

pushd "$target_dir"

rm -rf *online*
find . -name ".*" | while IFS= read -r file; do
  rm -rf "$file"
done
find . -type f ! -name "*.c"

popd
