#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 <JPLAG_RESULT_PATH>"
  exit 1
fi

java -jar "$HOME"/jplag/cli/target/jplag-*-jar-with-dependencies.jar \
    -M view \
    --result-file="$1/results.jplag"
