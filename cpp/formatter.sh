#!/bin/bash
for file in $(find . -name "*.*" | grep -E "\.(cc|hpp)$"); do
  echo $file
  clang-format --style=file:${HOME}/clang-format/.clang-format -i $file
  chmod 755 $file
done
