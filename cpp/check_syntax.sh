#!/bin/bash
DIR=$(dirname $0)
FILE_NAME="error_file_lists.txt"
MY_FLAGS="-c -fsyntax-only -std=c++14 -Wall -Wextra -Werror -fno-builtin"
>"$FILE_NAME"
for file in $(find "$DIR" -name "*.*" | grep -E "\.cc$"); do
  echo "$file"
  if [[ "$file" == *"_part"* || "$file" == *"_ignore"* ]]; then
    echo "  - Skip $file ... "
    continue
  fi
  # g++ $file $MY_FLAGS >/dev/null 2>&1
  g++ $file $MY_FLAGS 2>/dev/null
  if [ $? -ne 0 ]; then
    echo "$file" >>"$FILE_NAME"
    g++ $file $MY_FLAGS >>"$FILE_NAME" 2>&1
    echo "========================================" >>"$FILE_NAME"
  fi
done

cat "$FILE_NAME"
