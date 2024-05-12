#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;
    const char *msg1 = "Child1 is sending a message!\n";
    const char *msg2 = "Child2 is sending a message!\n";

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create child process 1
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0)
    {                 // Child process 1
        close(fd[0]); // Close reading end

        // Lock file descriptor for writing
        lockf(fd[1], F_LOCK, 0);
        write(fd[1], msg1, strlen(msg1));
        lockf(fd[1], F_ULOCK, 0); // Release lock

        close(fd[1]);
        exit(EXIT_SUCCESS);
    }

    // Create child process 2
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0)
    {                 // Child process 2
        close(fd[0]); // Close reading end

        // Lock file descriptor for writing
        lockf(fd[1], F_LOCK, 0);
        write(fd[1], msg2, strlen(msg2));
        lockf(fd[1], F_ULOCK, 0); // Release lock

        close(fd[1]);
        exit(EXIT_SUCCESS);
    }

    // Parent process
    close(fd[1]); // Close writing end
    char buf[256];
    ssize_t bytes_read;

    while ((bytes_read = read(fd[0], buf, sizeof(buf))) > 0)
    {
        write(STDOUT_FILENO, buf, bytes_read);
    }

    close(fd[0]);

    // Wait for child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
