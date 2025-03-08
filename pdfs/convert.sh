#!/bin/bash

for file in $(find ../ -name "*.md" | grep -P '\d{2}\.md$'); do
  echo $file
done
