#!/bin/bash

set -e  # 오류 발생 시 스크립트 종료

# 1. 고정된 대상 디렉토리
TARGET_DIR="/home/ktj/Operating_System/Assignement#11"

# 2. 인자 확인
if [ $# -lt 1 ]; then
  echo "사용법: $0 <확장자1> [확장자2] ..."
  exit 1
fi

# 3. 대상 디렉토리 존재 확인
if [ ! -d "$TARGET_DIR" ]; then
  echo "오류: 디렉토리 '$TARGET_DIR' 이 존재하지 않습니다."
  exit 1
fi

# 4. 확장자별 폴더 만들기
for ext in "$@"; do
  mkdir -p "$TARGET_DIR/$ext"
done

# 5. others 폴더 생성
mkdir -p "$TARGET_DIR/others"

# 6. 파일 정리
find "$TARGET_DIR" -maxdepth 1 -type f | while read file; do
  fname=$(basename "$file")
  ext="${fname##*.}"

  if [[ "$fname" == "$ext" ]]; then
    # 확장자 없음
    mv "$file" "$TARGET_DIR/others/"
  else
    matched=0
    for arg in "$@"; do
      if [[ "$ext" == "$arg" ]]; then
        mv "$file" "$TARGET_DIR/$ext/"
        matched=1
        break
      fi
    done
    if [[ $matched -eq 0 ]]; then
      mv "$file" "$TARGET_DIR/others/"
    fi
  fi
done

echo "✅ 파일 정리가 완료되었습니다: $TARGET_DIR"

