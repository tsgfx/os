#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    // ①
    pid_t pid = fork();
    printf("In which process?\n"); // ②
    if (pid == 0)
    {
        sleep(3);
        printf("Child: pid=%d, ppid=%d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent: Child=%d, pid=%d, ppid=%d\n", pid, getpid(), getppid());
        printf("After Child ends.\n");
    }
    // ③
}