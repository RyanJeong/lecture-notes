#!/bin/bash

# Get base path from arguments
BASE_PATH="$1"
EVAL_DIR="$2"

if [ -z "$BASE_PATH" ] || [ -z "$EVAL_DIR" ]; then
  echo "ERROR: Both arguments are required"
  echo "Usage: $0 <base_path> <eval_dir>"
  exit 1
fi

# Convert BASE_PATH to absolute path
if [[ ! "$BASE_PATH" = /* ]]; then
  BASE_PATH="$(cd "$BASE_PATH" 2>/dev/null && pwd)"
  if [ $? -ne 0 ]; then
    echo "ERROR: Base path does not exist: $1"
    exit 1
  fi
else
  if [ ! -d "$BASE_PATH" ]; then
    echo "ERROR: Base path does not exist: $BASE_PATH"
    exit 1
  fi
fi

# Convert EVAL_DIR to absolute path
if [[ ! "$EVAL_DIR" = /* ]]; then
  EVAL_DIR="$(cd "$EVAL_DIR" 2>/dev/null && pwd)"
  if [ $? -ne 0 ]; then
    echo "ERROR: Eval dir does not exist: $2"
    exit 1
  fi
else
  if [ ! -d "$EVAL_DIR" ]; then
    echo "ERROR: Eval dir does not exist: $EVAL_DIR"
    exit 1
  fi
fi

# Check if check.sh exists in EVAL_DIR
if [ ! -f "$EVAL_DIR/check.sh" ]; then
  echo "ERROR: check.sh not found in $EVAL_DIR"
  exit 1
fi

# Remove trailing slashes
BASE_PATH="${BASE_PATH%/}"
EVAL_DIR="${EVAL_DIR%/}"

# Create results.txt if it doesn't exist
RESULTS_FILE="$BASE_PATH/results.txt"
if [ ! -f "$RESULTS_FILE" ]; then
  touch "$RESULTS_FILE"
else
  # To separate previous results
  echo >>"$RESULTS_FILE"
fi

# Find all a.out files and evaluate them
cd "$BASE_PATH" || exit 1

aout_files=$(find . -name "a.out" -type f 2>/dev/null | sort)

if [ -z "$aout_files" ]; then
  echo "[WARN] No a.out files found in $BASE_PATH"
  exit 0
fi

echo "Evaluation process started..."
echo ""

# Counter for tracking
total=0
success=0
failed=0

while IFS= read -r aout_path; do
  total=$((total + 1))

  # Get the directory containing a.out
  aout_dir=$(dirname "$aout_path")
  aout_name=$(basename "$aout_path")

  echo "[EVAL] Evaluating: $aout_path"

  # Run check.sh with the absolute path to a.out (60 second timeout)
  eval_output=$(timeout 60 "$EVAL_DIR/check.sh" "$BASE_PATH/$aout_path" 2>&1)
  eval_status=$?

  # Append result to results.txt
  echo >>"$RESULTS_FILE"
  echo "---" >>"$RESULTS_FILE"
  echo "Path: $aout_path" >>"$RESULTS_FILE"

  if [ $eval_status -eq 124 ]; then
    echo "Status: FAIL" >>"$RESULTS_FILE"
    echo "TIMEOUT: Execution exceeded 60 seconds" >>"$RESULTS_FILE"
    failed=$((failed + 1))
  elif [ $eval_status -eq 0 ]; then
    echo "Status: PASS" >>"$RESULTS_FILE"
    success=$((success + 1))
  else
    echo "Status: FAIL" >>"$RESULTS_FILE"
    failed=$((failed + 1))
  fi

  echo "$eval_output" >>"$RESULTS_FILE"
  echo ""

done <<<"$aout_files"

echo "Evaluation process completed!"
echo "Total: $total, Success: $success, Failed: $failed"
echo ""
echo "Results saved to: $RESULTS_FILE"
