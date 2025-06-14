#!/bin/bash

for dir_name in $(find . -maxdepth 1 -mindepth 1 -type d -printf '%f\n' | grep -E '^[0-9_]+$'); do
  echo "$dir_name"
  pushd "$dir_name" >/dev/null

  port=$((port + 1))

  java -jar "$HOME"/jplag/cli/target/jplag-*-jar-with-dependencies.jar \
      -l cpp \
      -M run \
      --overwrite ./

  popd >/dev/null
done

