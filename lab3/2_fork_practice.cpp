// Copyright@Guo Ruichao
#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{

    pid_t child1 = fork();
    pid_t child2;
    // 父进程
    if (child1 > 0)
    {
        cout << "a" << endl;
        // 创建子进程2
        child2 = fork();
        // 子进程2
        if (child2 == 0)
        {
            cout << "c" << endl;
        }
    }
    // 子进程1
    if (child1 == 0)
    {
        cout << "b" << endl;
    }

    return 0;
}