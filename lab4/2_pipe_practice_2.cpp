// Copyright@Guo Ruichao
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t child1, child2;
    const char *message1 = "Child1 is sending a message!\n";
    const char *message2 = "Child2 is sending a message!\n";
    char buf[256];

    // 创建管道
    pipe(fd);
    // 创建子进程1
    child1 = fork();
    if (child1 == 0)
    {
        // 写时关闭读端
        close(fd[0]);

        // 加锁
        lockf(fd[1], 1, 0);
        printf("child1 is writing pipe !\n");
        write(fd[1], message1, strlen(message1));
        lockf(fd[1], 0, 0);
        // 解锁

        // 关闭写端
        close(fd[1]);
        exit(0);
    }

    // 创建子进程2
    child2 = fork();
    if (child2 == 0)
    {
        // 写时关闭读端
        close(fd[0]);

        // 加锁
        lockf(fd[1], 1, 0);
        printf("child2 is writing pipe !\n");
        write(fd[1], message2, strlen(message2));
        lockf(fd[1], 0, 0);
        // 解锁

        // 关闭写端
        close(fd[1]);
        exit(0);
    }

    // 父进程
    // 读时关闭写端
    close(fd[1]);
    ssize_t bytes_read;
    while ((bytes_read = read(fd[0], buf, sizeof(buf) - 1)) > 0)
    {
        wait(0);                // 等待子进程结束
        buf[bytes_read] = '\0'; // 给消息添加终止符
        printf("%s", buf);      // 输出消息
    }
    // 关闭读端
    close(fd[0]);

    return 0;
}
