#!/bin/bash
for file in $(find . -name "*.*" | grep -E "\.(c|h)$"); do
  echo $file
  clang-format --style=file:/home/docker/clang-format/.clang-format-knr -i $file
  chmod 755 $file
done
