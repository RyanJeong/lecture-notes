#!/bin/bash
EXT="pdf"
EXT="pptx"
DIR="$(dirname "$0")"

for file in $(find ./ -name README.md | grep -P '\d{2}\/'); do
  LECTURE=$(basename $(dirname $(dirname ${file})))
  CHAPTER=$(basename $(dirname ${file}))
  echo "convert ${file} to "$DIR"/${LECTURE}_${CHAPTER}.${EXT}"
done
