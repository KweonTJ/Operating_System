#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char* myfifo = "/tmp/myfifo";
    char buf[128];
    //char *message = "Hello, World!\n";

    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_RDONLY);
    read(fd, buf, 128);
    printf("%s \n", buf);
    //write(fd, message, strlen(message));
    close(fd);

    return 0;
}