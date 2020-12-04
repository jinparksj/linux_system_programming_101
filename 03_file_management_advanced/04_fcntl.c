#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    //FD macros:
    //STDIN_FILENO: 0
    //STDOUT_FILENO: 1
    //STDERR_FILENO: 2
    //fcntl: Flag Control
    int ret;
    int flag;
    char buf[128];
    int fd;

    fd = STDIN_FILENO;
    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    printf("read() [%s] - %d bytes\n", buf, ret);
    
    flag = fcntl(fd, F_GETFL);
    
    if (flag == -1) {
        printf("fcntl(F_GETFL) fail\n");
        return -1;
    }

    ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);

    
    if (flag == -1) {
        printf("fcntl(F_SETFL) fail\n");
        return -1;
    }
    

    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));

    printf("read() [%s] - %d bytes\n", buf, ret);

    if (ret == -1) {
        printf("errono=%d, %s\n", errno, strerror(errno)); 
    }
    return 0;
}
