#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

int main(void) {
    int i;
    struct tms buf;
    clock_t t1, t2, clk;

    clk = sysconf(_SC_CLK_TCK);
    printf("Clock tick: %ld\n", clk);

    t1 = times(&buf);
    
    int fd = open("temp_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char msg[] = "Hello, system call!\n";
    size_t msg_len = strlen(msg);
    
    for (i = 0; i < 1000000; i++) {
        if (write(fd, msg, msg_len) < 0) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }
    close(fd);
    
    sleep(1);

    t2 = times(&buf);

    printf("t1: %ld\n", t1);
    printf("t2: %ld\n", t2);
    printf("utime  (user time):   %.2f sec\n", (double)buf.tms_utime / clk);
    printf("stime  (system time): %.2f sec\n", (double)buf.tms_stime / clk);
    printf("real time:            %.2f sec\n", (double)(t2 - t1) / clk);

    double total_time = ((double)buf.tms_utime + buf.tms_stime) / clk;
    printf("user + system time:   %.2f sec\n", total_time);

    // 검증
    if ((double)(t2 - t1) / clk >= total_time)
        printf("O: 프로세스 실행 시간 = 시스템 실행 시간 + 사용자 실행 시간\n");
    else
        printf("X: 두 시간의 합보다 real time이 더 작음\n");
    
    return 0;
}
