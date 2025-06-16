#!/bin/bash

# Munseong: Here is the required structure for each assignment (SRC_DIR).
#           It must include input files, output files, a build script, and a
#           reference source code file:
# $ tree
# .
# ├── check.sh    # Build script
# ├── in1         # Input file 1 (Required)
# ├── in2         # Input file 2 (Optional)
# ├── in3         # Input file 3 (Optional)
# ├── in4         # Input file 4 (Optional)
# ├── in5         # Input file 5 (Optional)
# ├── out1        # Expected output for in1 (Required)
# ├── out2        # Expected output for in2 (Required if in2 is exists)
# ├── out3        # Expected output for in3 (Required if in3 is exists)
# ├── out4        # Expected output for in4 (Required if in4 is exists)
# ├── out5        # Expected output for in5 (Required if in5 is exists)
# └── src
#     └── ref.c   # Reference source

if [ $# -ne 3 ]; then
  echo "Usage: $0 <ASMT_SRC_DIR_PATH> <ASMT_DEST_DIR_PATH> <RAND_SIZE>"
  exit 1
fi

TMPDIR=$(mktemp -d)
RAND_SIZE="$3"
trap 'rm -rf "$TMPDIR"' EXIT  # automatically remove the tmp directory on exit

obfuscate_lines() {
  while IFS= read -r line || [[ -n "$line" ]]; do
    read -ra tokens <<< "$line"
    output=""
    for ((i = 0; i < ${#tokens[@]}; ++i)); do
      output+="${tokens[i]}"
      if (( i < ${#tokens[@]} - 1 )); then
        spaces=$((RANDOM % RAND_SIZE + 2))  # generate 2 (0 + 2) ~ 5 (3 + 2) random spaces
        output+="$(printf '%*s' "$spaces")"
      fi
    done
    echo "$output"
  done
}

cp -r "$1" "$TMPDIR"
SRC_DIR_NAME=$(basename $1)
SRC_DIR_PATH="$TMPDIR"/"$SRC_DIR_NAME"
echo "src: $SRC_DIR_PATH"

# obfuscate to 'in' files
if [ "$RAND_SIZE" -gt 0 ]; then
  for file in $(find ${SRC_DIR_PATH} -name 'in*'); do
    output_file_name="$file"_tmp
    cat $file | obfuscate_lines >> $output_file_name
    mv "$output_file_name" "$file"
  done
fi

# verify
target_path=$(find "$SRC_DIR_PATH"/src -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" \))

# DEBUG
# bash "$SRC_DIR_PATH"/check.sh "$target_path" "$SRC_DIR_PATH"

bash "$SRC_DIR_PATH"/check.sh "$target_path" "$SRC_DIR_PATH" >/dev/null
verify_ret=$?
if [ $verify_ret -ne 0 ]; then
  echo "Data is invalid. Aborting."
  exit 1
fi

cp -r "$2" "$TMPDIR"
DEST_DIR_NAME="$(basename "$2")"
DEST_DIR_PATH="$TMPDIR"/"$DEST_DIR_NAME"
echo "dest: $DEST_DIR_PATH"

target_path=$(find "$DEST_DIR_PATH" -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.cc" -o -name "*.cxx" \))
result_path="$TMPDIR"/results.txt
>"$result_path"
bash "$SRC_DIR_PATH"/check.sh "$target_path" "$SRC_DIR_PATH" >> $result_path

mkdir -p $(dirname "$2")/results_summary
mv "$result_path" $(dirname "$2")/results_summary/$(basename "$2").txt

# debug
# cat "$2"/results.txt
