#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("PID: %ld\n",(int)getpid());
    printf("PPID: %ld\n",(int)getppid());
}