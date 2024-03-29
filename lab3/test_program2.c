#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid; // 声明变量pid作为fork的返回值

    pid = fork(); // 创建子进程

    if(pid == -1) // 检查fork是否成功
    {
        perror("fork");
        return 1;
    }
    else if(pid == 0) // 子进程
    {
        sleep(3);
        printf("Child: pid=%d, ppid=%d\n", getpid(), getppid());
    }
    else // 父进程
    {
        printf("Parent: Child=%d, pid=%d, ppid=%d\n", pid, getpid(), getppid());
        wait(NULL); // 等待子进程结束
        printf("After Child ends.\n");
    }

    printf("In which process?\n"); // 父子进程共有的部分
    return 0;
}
