#!/bin/bash

DIR=$(dirname $0)
for file in $(find "$DIR" -type f \( -name "temp.pdf" -o -name "temp.md" -o -name "temp.pptx" -o -name "a.out" -o ! -name "*.*" \)); do
  echo "Removing $file ..."
  rm $file
done
