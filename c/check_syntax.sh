#!/bin/bash
FILE_NAME="error_file_lists.txt"
MY_FLAGS="-c -fsyntax-only -ansi -Wall -Wextra -Werror -fno-builtin"
> "$FILE_NAME"
for file in $(find . -name "*.*" | grep -E "\.c$"); do
  echo "$file"
  if [[ "$file" == *"_part"* || "$file" == *"_ignore"* ]]; then
    echo "  - Skip $file ... "
    continue
  fi
  gcc $file $MY_FLAGS > /dev/null 2>&1
  if [ $? -ne 0 ]; then
    echo "$file" >> "$FILE_NAME"
    gcc $file $MY_FLAGS >> "$FILE_NAME" 2>&1
    echo "========================================" >> "$FILE_NAME"
  fi
done

cat "$FILE_NAME"
