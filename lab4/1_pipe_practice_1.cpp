// Copyright@Guo Ruichao
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int x, fd[2];
    char buf[30], s[30];
    pipe(fd);
    while ((x = fork()) == -1)
        ;
    if (x == 0)
    {
        sprintf(buf, "this is an example\n");
        printf("child procee running ! \n");
        write(fd[1], buf, 30); /*把buf中的字符写入管道*/
        sleep(5);              /*睡眠5秒，让父进程读*/
        exit(0);               /*关闭x，子进程自我中止*/
    }
    else
    {
        wait(0); /*父进程挂起直到其某一子进程中止为止*/
        read(fd[0], s, 30);
        printf("% s", s);
    }
}