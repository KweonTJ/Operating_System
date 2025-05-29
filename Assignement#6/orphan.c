#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
    int x = 0;
    pid_t pid = fork();
    if (pid > 0)
    {
        x = 1;
        printf("Parent Process => PID: %d, PPID: %d x : %d\n", getpid(), getppid(), x);
        return 0;
    }
    else if (pid == 0)
    {
        x = 2;
        sleep(2);
        printf("Child Process => PID: %d, PPID: %d x : %d\n", getpid(), getppid(), x);
        while(1) {sleep(1);}
    }
    else
    {
        printf("fork failed!\n");
        return -1;
    }
    return 0;
}