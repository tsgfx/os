#include <iostream>
#include <cstring>
using namespace std;

#define PROC_NUM 5

typedef char PROC_STATE;

// 进程控制结构体
typedef struct _proc
{                     /*进程结构体*/
    char name[32];    /*进程名*/
    int run_time;     /*要求运行总时间*/
    int alloc_time;   /*已经运行时间*/
    int req_time;     /*还需要的运行时间*/
    int pri;          /*优先级：时间片调度中未使用*/
    PROC_STATE state; /*进程状态*/
    struct _proc *next;
} PROC;

// 初始化就绪队列
PROC *initPROCQueue()
{
    // 初始化进程信息
    char names[PROC_NUM][32] = {"P1", "P2", "P3", "P4", "P5"};
    int run_times[PROC_NUM] = {2, 3, 1, 2, 4};
    int pris[PROC_NUM] = {1, 5, 3, 4, 2};

    // 初始化就绪队列
    PROC *front = nullptr;
    PROC *rear = nullptr;
    for (int i = 0; i < PROC_NUM; i++)
    {
        PROC *newPROC = new PROC;
        strcpy(newPROC->name, names[i]);
        newPROC->run_time = run_times[i];
        newPROC->alloc_time = 0;
        newPROC->req_time = run_times[i];
        newPROC->pri = pris[i];
        newPROC->state = 'R';
        newPROC->next = nullptr;
        if (front == nullptr)
        {
            front = rear = newPROC;
        }
        else
        {
            rear->next = newPROC;
            rear = newPROC;
        }
    }
    return front;
}

// 对就绪队列按优先级从大到小排序
void sortBasedOnPri(PROC *front)
{
    PROC *p = front;
    while (p != nullptr)
    {
        PROC *q = p->next;
        while (q != nullptr)
        {
            if (p->pri < q->pri)
            {
                swap(p->name, q->name);
                swap(p->run_time, q->run_time);
                swap(p->alloc_time, q->alloc_time);
                swap(p->req_time, q->req_time);
                swap(p->pri, q->pri);
                swap(p->state, q->state);
            }
            q = q->next;
        }
        p = p->next;
    }
}

// 打印进程队列
void printPROCQueue(PROC *head)
{
    PROC *p = head;
    cout << "进程名\t指针\t总运行时间\t已运行时间\t需要时间\t优先数\t状态" << endl;
    while (p != nullptr)
    {
        cout << p->name << "\t" << (p->next == nullptr ? "0" : p->next->name) << "\t"
             << p->run_time << "\t\t" << p->alloc_time << "\t\t" << p->req_time << "\t\t"
             << p->pri << "\t" << p->state << endl;
        p = p->next;
    }
    cout << "----------------------------------------------------------------------------" << endl;
}

// 处理器调度程序
void schedualPROCQueue(PROC *head)
{
    PROC *p = head;
    if (p != nullptr)
    {
        cout << "选中的进程为: " << p->name << endl;
        p->alloc_time++;
        p->req_time--;
        p->pri--; // 当进程被调度时优先级-1

        // 如果进程运行结束，修改状态为'E'
        if (p->req_time == 0)
        {
            p->state = 'E';
            head = p->next;
            delete p; // 把结束的进程移出队列
        }
        // 每次调度完都按优先数从大到小进行排序
        sortBasedOnPri(head);
        cout << "调度后的就绪队列为:" << endl;
        printPROCQueue(head);
        cout << endl;
    }
}

// 检查所有进程是否结束
bool isEnd(PROC *head)
{
    PROC *p = head;
    while (p != nullptr)
    {
        if (p->state == 'R')
            return false;
        p = p->next;
    }
    return true;
}

int main()
{
    // 初始化就绪队列
    PROC *PROCQueue = initPROCQueue();
    cout << "初始就绪队列为:" << endl;
    printPROCQueue(PROCQueue);

    // 对就绪队列按优先级排序
    sortBasedOnPri(PROCQueue);
    cout << endl;
    cout << "排序后的就绪队列为:" << endl;
    printPROCQueue(PROCQueue);
    cout << endl;

    // 对就绪队列按优先级调度
    int i = 1;
    while (PROCQueue != nullptr)
    {
        cout << "第" << i << "次调度" << endl;
        i++;
        schedualPROCQueue(PROCQueue);
    }
    return 0;
}
