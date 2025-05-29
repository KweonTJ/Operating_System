#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_def.h"

int main() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        return 1;
    }

    printf("[Listener] 메시지를 기다리는 중...\n");

    while (1) {
        if (strlen(data) > 0) {
            printf("[Listener] 수신된 메시지: %s\n", data);
            data[0] = '\0'; // 메시지 클리어
        }
        sleep(1);
    }

    return 0;
}
