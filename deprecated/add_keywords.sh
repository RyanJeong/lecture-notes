#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <source_text_file>"
    exit 1
fi

SRC_FILE="$1"
# TARGET_FILE="/usr/lib/node_modules/@marp-team/marp-cli/node_modules/highlight.js/lib/languages/c.js"
# TARGET_FILE="./highlight/languages/c.js"
TARGET_FILE="./highlight/languages/cpp.js"

# Create a temporary directory for storing temp files
TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT # Cleanup temp directory on script exit

# Temporary files
TMP_EXTRACTED="$TMP_DIR/tmp_extracted_functions.txt"
TMP_UNIQUE="$TMP_DIR/tmp_unique_functions.txt"
TMP_FILTERED="$TMP_DIR/tmp_filtered_functions.txt"

# Step 1: Extract function names matching C FUNC_NAME( pattern
grep -oP '\b[a-zA-Z_][a-zA-Z0-9_]*(?=\()' "$SRC_FILE" |
    grep -vP '^[A-Z0-9_]+$' >"$TMP_EXTRACTED"

# Step 2: Sort and remove duplicates
sort -u "$TMP_EXTRACTED" >"$TMP_UNIQUE"

# Step 3: Filter out function names that already exist in the **entire target file**
touch "$TMP_FILTERED"
>"$TMP_FILTERED"

EXTRACTED=$(awk '
  /built_in:/ {flag=1}
  /_type_hints: TYPE_HINTS/ {flag=0; exit}
  flag
' "$TARGET_FILE")
while read -r func; do
    # Check if the exact function name exists anywhere in the JS file
    if ! echo "$EXTRACTED" | grep -w "$func" >/dev/null 2>&1; then
        echo "$func" >>"$TMP_FILTERED"
    fi
done <"$TMP_UNIQUE"

# Step 4: Store the final filtered function names in a variable
# RESULT=$(tr '\n' ' ' < "$TMP_FILTERED" | sed 's/  */ /g' | sed 's/^ *//;s/ *$//')
RESULT=$(tr '\n' ' ' <"$TMP_FILTERED" | sed 's/  */ /g')

if [[ -z $(echo "$RESULT" | tr -d '[:space:]') ]]; then
    exit 0
fi

# Debug
NEW_BUILTINS="built_in: '$RESULT'"
echo "$NEW_BUILTINS"
echo "========"

# Use awk to insert the new line while modifying the original built_in: line to +
awk -v new_builtins="$NEW_BUILTINS" '
    {
        if ($0 ~ /built_in:/ && !inserted) {
            print new_builtins;  # Insert the new built_in above the first occurrence
            inserted = 1;
        }
        if ($0 ~ /built_in:/ && inserted) {
            sub(/built_in:/, "  +");  # Convert built_in: to +
        }
        print;
    }
' "$TARGET_FILE" > >(tee "$TARGET_FILE")
