// Copyright@Guo Ruichao
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child1, child2;
// 子进程1的信号处理程序
void child1Exit(int sig)
{
    printf("Child process 1 is killed by parent !!\n");
    exit(0);
}

// 子进程2的信号处理程序
void child2Exit(int sig)
{
    printf("Child process 2 is killed by parent !!\n");
    exit(0);
}

// 父进程的信号处理程序
void parentExit(int sig)
{
    // 向子进程发送信号
    kill(child1, 16);
    kill(child2, 17);
}

int main()
{
    // 创建第一个子进程
    if ((child1 = fork()) == 0)
    {
        signal(16, child1Exit); // 设置信号处理程序
        while (1)
            ;
    }
    // 创建第二个子进程
    if ((child2 = fork()) == 0)
    {
        signal(17, child2Exit); // 设置信号处理程序
        while (1)
            ;
    }
    // 父进程
    signal(2, parentExit); // 设置信号处理程序
    // 等待子进程终止
    wait(0);
    wait(0);
    printf("Parent process is killed!!\n");
    return 0;
}
