#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char buffer[100];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스
        close(pipe1[1]); // 읽기만
        close(pipe2[0]); // 쓰기만

        read(pipe1[0], buffer, sizeof(buffer));
        printf("[Child - PID %d] Received: %s\n", getpid(), buffer);

        const char* reply = "Hello parent";
        write(pipe2[1], reply, strlen(reply) + 1);

        close(pipe1[0]);
        close(pipe2[1]);
    } else {
        // 부모 프로세스
        close(pipe1[0]); // 쓰기만
        close(pipe2[1]); // 읽기만

        const char* msg = "Hello child";
        write(pipe1[1], msg, strlen(msg) + 1);

        read(pipe2[0], buffer, sizeof(buffer));
        printf("[Parent - PID %d] Received: %s\n", getpid(), buffer);

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}
