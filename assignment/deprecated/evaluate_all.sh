#!/bin/bash
# e.g., ./evaluate_all.sh dju_asmt/c_asmt1 2025_1_565006_01_1_553292 4
# e.g., ./evaluate_all.sh dju_asmt/c_asmt2 2025_1_565006_01_2_553423 4
# e.g., ./evaluate_all.sh dju_asmt/c_asmt3 2025_1_565006_01_3_553921 0

if [ $# -ne 3 ]; then
  echo "Usage: $0 <ASMT_SRC_DIR_PATH> <ASMT_DEST_DIR_PATH> <RAND_SIZE>"
  exit 1
fi

ASMT_SRC_DIR_PATH="$1"
RAND_SIZE="$3"
find "$2" -mindepth 1 -maxdepth 1 -type d |
  while IFS= read -r path; do
    ./evaluate_dir.sh "$ASMT_SRC_DIR_PATH" "$path" "$RAND_SIZE"
  done
