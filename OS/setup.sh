#!/bin/bash
set -e

#––– 설정 변수 ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
BASE_IMAGE=osrf/ros:melodic-desktop-full
BASE_USER=kweontakju
NEW_USER=coffee

PROJECT_DIR=$HOME/ros_melodic_project
HOST_OS_DIR=$HOME/OS

CTR1=ros_melodic_user
IMG1=ros_melodic_with_user

IMG2=ros_melodic_two_users
CTR2=ros_melodic_coffee
#–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

mkdir -p "$PROJECT_DIR" "$HOST_OS_DIR"
cd "$PROJECT_DIR"

# 1. Dockerfile 생성
cat > Dockerfile <<EOF
FROM $BASE_IMAGE

ARG USERNAME=$BASE_USER

RUN apt-get update \\
 && apt-get install -y sudo \\
 && useradd -m -s /bin/bash \${USERNAME} \\
 && echo "\${USERNAME} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER \${USERNAME}
WORKDIR /home/\${USERNAME}

ENTRYPOINT ["/bin/bash"]
EOF

# 2. 첫 번째 이미지 빌드 (kweontakju 계정 포함)
docker build -t $IMG1 .

# 3. 기존 컨테이너 제거
docker rm -f $CTR1 2>/dev/null || true

# 4. 첫 컨테이너 실행 (백그라운드 대기)
docker run -d --name $CTR1 \
  -u $BASE_USER \
  -w /home/$BASE_USER \
  -v $HOST_OS_DIR:/home/$BASE_USER/OS \
  $IMG1 -c "tail -f /dev/null"

# 5. 볼륨 테스트 (파일 생성)
docker exec $CTR1 bash -lc "echo 'hello from $CTR1' > /home/$BASE_USER/OS/container_test.txt"

# 6. 새 user 추가
docker exec $CTR1 sudo useradd -m -s /bin/bash $NEW_USER

# 7. 커밋하여 두 번째 이미지 생성
docker commit $CTR1 $IMG2

# 8. 첫 컨테이너 정리
docker rm -f $CTR1

# 9. 최종 컨테이너 실행 (coffee 계정으로 자동 로그인)
docker run -it --rm --name $CTR2 \
  --entrypoint "" \
  -u $NEW_USER \
  -w /home/$NEW_USER \
  -v $HOST_OS_DIR:/home/$NEW_USER/OS \
  $IMG2 bash
