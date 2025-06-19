#!/bin/bash

LOG_DIR="/home/ktj/log_data"

TODAY=$(date +"%Y-%m-%d")

ARCHIVE_NAME="logs_$(date +"%Y-%m-%d").tar.gz"

LOG_FILES=$(find "$LOG_DIR" -type f -name "*.log" ! -name "*$TODAY*")

if [[ -n "$LOG_FILES" ]]; then
    tar -czf "$ARCHIVE_NAME" -C "$LOG_DIR" $(echo "$LOG_FILES" | sed "s|$LOG_DIR/||g")
    echo "압축 완료: $ARCHIVE_NAME"
else
    echo "오늘 날짜를 제외한 로그 파일이 없습니다."
fi
