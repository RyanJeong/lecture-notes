#!/bin/bash
for file in $(find . -name results.txt | grep -v "/backup/"); do
  echo "$file"
  cat "$file"
  echo
done
