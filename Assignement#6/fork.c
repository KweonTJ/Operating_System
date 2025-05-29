#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("os\n");
    if (fork() == 0)
    {
        printf("process\n");
        if (fork() == 0)
        {
            printf("fork\n");
        }
    }
    printf("clear\n");
}