#!/bin/bash

# TBD
# TARGETS="c cpp"

TARGETS="c"

for target in $TARGETS; do
  "$(dirname $0)/${target}/$(basename $0)"
done
