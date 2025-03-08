#!/bin/bash
EXT="pdf"
for file in $(find ../ -name README.md | grep -P '\d{2}\/'); do
  LECTURE=$(basename $(dirname $(dirname ${file})))
  CHAPTER=$(basename $(dirname ${file}))
  echo "convert ${file} to ${LECTURE}_${CHAPTER}.${EXT}"
done
