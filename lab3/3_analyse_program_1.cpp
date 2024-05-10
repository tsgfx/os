#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int x, i;

    printf("Input a initial value for i: ");
    scanf("%d", &i);
    while ((x = fork()) == -1)
        ;
    if (x == 0) /* child run */
    {
        printf("When child runs, i=%d\n", i);
        printf("Input a value in child: ");
        scanf("%d", &i);
        printf("i=%d\n", i);
    }
    else /* parent run */
    {
        wait(nullptr);
        printf("After child runs, in parent, i=%d\n", i);
    }
}
