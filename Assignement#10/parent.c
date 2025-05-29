#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char* myfifo = "/tmp/myfifo";
    char *message = "Hello, World!\n";

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);
    write(fd, message, strlen(message));
    close(fd);

    return 0;
}