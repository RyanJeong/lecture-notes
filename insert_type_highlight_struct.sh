#!/bin/bash

if [ $# -ne 1 ]; then
  echo "Usage: $0 <{c|cpp}.js PATH>"
  exit 1
fi

# Target JavaScript file to modify
TARGET_FILE="$1"

# Match pattern for the struct/union/enum highlighting block
INSERT_PATTERN="className: 'type', match: /\\b(struct|union|enum)\\s+[a-zA-Z_]\\w*/"

# Check if the block already exists
if grep -q "Highlight struct/union/enum definitions properly" "$TARGET_FILE"; then
  echo "The struct/union/enum highlighting block already exists. No changes made."
  exit 0
fi

# Locate the line containing "PREPROCESSOR,"
LINE_NUM=$(grep -n "beginKeywords: 'enum class struct union'" "$TARGET_FILE" | head -n 1 | cut -d: -f1)

if [ -z "$LINE_NUM" ]; then
  echo "Could not locate PREPROCESSOR reference. Insertion aborted."
  exit 1
fi

# Add 1 to insert after that line
INSERT_AT=$((LINE_NUM - 2))

# Use sed to insert the block in-place
sed -i "${INSERT_AT}i\\
        {\\
          // Highlight struct/union/enum definitions properly\\
          className: 'type',\\
          match: /\\\b(struct|union|enum)\\\s+[a-zA-Z_]\\\w*/,\\
          relevance: 10\\
        },
" "$TARGET_FILE"

echo "The struct/union/enum highlighting block has been inserted successfully."

