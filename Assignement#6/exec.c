#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("--> Before exec function\n");

    if (execlp("ls", "ls", "-a", (char *)NULL) == -1)
    {
        perror("execlp");
        exit(1);
    }
    printf("--> After exec function\n");

    return 0;
}