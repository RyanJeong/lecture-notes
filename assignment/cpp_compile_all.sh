#!/bin/bash

# Get base path from argument
BASE_PATH="$1"

if [ -z "$BASE_PATH" ]; then
    echo "ERROR: Base path argument required"
    echo "Usage: $0 <base_path>"
    exit 1
fi

# Convert to absolute path
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

# Remove trailing slash from BASE_PATH
BASE_PATH="${BASE_PATH%/}"

# Create results.txt if it doesn't exist
RESULTS_FILE="$BASE_PATH/results.txt"
if [ ! -f "$RESULTS_FILE" ]; then
    touch "$RESULTS_FILE"
else
    # To separate previous results
    echo >>"$RESULTS_FILE"
fi

# Iterate through student folders and compile source code
cd "$BASE_PATH" || exit 1

for student_dir in */; do
    if [ ! -d "$student_dir" ]; then
        continue
    fi

    # Find all C/C++ source files in the folder, excluding __MACOSX and ._* files
    # Use mapfile to properly handle filenames with spaces
    mapfile -t cpp_files < <(find "$student_dir" -type f \( -name "*.cc" -o -name "*.cpp" -o -name "*.c" \) ! -path "*/__MACOSX/*" ! -name "._*" -print0 2>/dev/null | tr '\0' '\n')

    if [ ${#cpp_files[@]} -eq 0 ]; then
        echo "[FAIL] No source files found: $student_dir"
        # Append error to results.txt
        echo "---" >>"$RESULTS_FILE"
        echo "Path: $BASE_PATH/$student_dir" >>"$RESULTS_FILE"
        echo "Status: COMPILATION FAILED" >>"$RESULTS_FILE"
        echo "Reason: No source files found (*.c, *.cc, *.cpp)" >>"$RESULTS_FILE"
        echo "Files in directory:" >>"$RESULTS_FILE"
        ls -R "$student_dir" >>"$RESULTS_FILE" 2>&1
        continue
    fi

    # Compile
    echo "[BUILD] Compiling: $student_dir"
    compile_output=$(g++ -o "${student_dir}a.out" "${cpp_files[@]}" -lpthread -lm 2>&1)
    compile_status=$?

    if [ $compile_status -eq 0 ]; then
        echo "[OK] Compiled: ${student_dir}a.out"
    else
        echo "[FAIL] Compilation failed: $student_dir"
        # Append error to results.txt using absolute path
        echo "---" >>"$RESULTS_FILE"
        echo "Path: $BASE_PATH/$student_dir" >>"$RESULTS_FILE"
        echo "Status: COMPILATION FAILED" >>"$RESULTS_FILE"
        echo "$compile_output" >>"$RESULTS_FILE"
    fi
    echo ""
done

echo "Build process completed!"
