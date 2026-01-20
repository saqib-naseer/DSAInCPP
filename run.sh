#!/bin/bash

FILE="$1"

if [[ -z "$FILE" ]]; then
  echo "❌ No file provided"
  exit 1
fi

echo "▶ Running: $FILE"

g++ -std=c++17 "$FILE" -o temp_bin && ./temp_bin
