#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// null
int main()
{
    pid_t pid1, pid2;

    // 创建第一个子进程
    pid1 = fork();

    if (pid1 == 0)
    {
        // 子进程1
        printf("b\n");
    }
    else if (pid1 > 0)
    {
        // 父进程
        // 创建第二个子进程
        pid2 = fork();

        if (pid2 == 0)
        {
            // 子进程2
            printf("c\n");
        }
        else if (pid2 > 0)
        {
            // 父进程
            printf("a\n");
        }
        else
        {
            // 创建子进程失败
            perror("fork");
            return 1;
        }
    }
    else
    {
        // 创建子进程失败
        perror("fork");
        return 1;
    }

    return 0;
}
