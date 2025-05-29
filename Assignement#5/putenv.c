#include <stdio.h>
#include <stdlib.h>

int main() {
    char *val;

    // 변경 전 LOGNAME 출력
    val = getenv("LOGNAME");
    if (val == NULL)
        printf("변경 전 LOGNAME: (정의되지 않음)\n");
    else
        printf("변경 전 LOGNAME: %s\n", val);

    // LOGNAME 환경 변수 변경
    if (putenv("LOGNAME=robot_user") != 0) {
        perror("putenv 실패");
        return 1;
    }

    // 변경 후 LOGNAME 출력
    val = getenv("LOGNAME");
    if (val != NULL)
        printf("변경 후 LOGNAME: %s\n", val);

    return 0;
}
