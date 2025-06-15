#!/bin/bash
# e.g., ./evaluate_all.sh c_asmt/asmt1 2025_1_565006_01_1_553292

if [ $# -ne 2 ]; then
  echo "Usage: $0 <ASMT_SRC_DIR_PATH> <ASMT_DEST_DIR_PATH>"
  exit 1
fi

ASMT_SRC_DIR_PATH="$1"
find "$2" -mindepth 1 -maxdepth 1 -type d \
    | while IFS= read -r path; do
  ./evaluate_dir.sh "$ASMT_SRC_DIR_PATH" "$path"
done