#!/bin/bash

directory="/home/ktj/analysis_project/files"

echo "# Analysis Report"
echo "## File Count by Extension"

declare -A file_types
file_types["- Test files:"]=0
file_types["- Script files:"]=0
file_types["- Hidden files:"]=0

while IFS= read -r file; do
    filename=$(basename "$file")
    ext="${file##*.}"
    if [[ "$filename" == .* ]]; then
        ((file_types["- Hidden files:"]++))
    elif [[ "$ext" == "txt" ]]; then
        ((file_types["- Test files:"]++))
    elif [[ "$ext" == "sh" ]]; then
        ((file_types["- Script files:"]++))
    fi
done < <(find "$directory" -type f)

for type in "- Test files:" "- Script files:" "- Hidden files:"; do
    echo "$type ${file_types[$type]}"
done

echo -e "\n## Text File Analysis"
find "$directory" -type f -name "*.txt" | sort | while read file; do
    filename=$(basename "$file")
    if [[ "$filename" == .* ]]; then
        continue 
    fi
    line_count=$(wc -l < "$file")
    word_count=$(wc -w < "$file")
    char_count=$(wc -m < "$file")
    echo "- $filename:"
    echo -e "\t- Lines: $line_count"
    echo -e "\t- Words: $word_count"
    echo -e "\t- Characters: $char_count"
done
