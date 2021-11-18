//队列C语言实现
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define MAXSIZE 10 //存储数据元素的最大个数
#define ERROR -99 //ElementType的特殊值，标志错误

typedef struct Queue
{
    int data[MAXSIZE];
    int front; //记录队列头部
    int rear;  //记录队列尾部
    int size;  //存储数据元素个数
}queue;

queue* CreateQueue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    if (!q)
    {
        cout<<"创建失败"<<endl;
        return NULL;
    }
    q->front = -1;
    q->rear = -1;
    q->size = 0;
    return q;
}

bool isFullQ(queue *q)
{
    return (q->size == MAXSIZE);
}

void addQueue(queue *q, int data)
{
    if(isFullQ(q))
    {
        cout<<"队列已满"<<endl;
        return ;
    }
    q->rear++;
    q->rear %= MAXSIZE;
    q->size++;
    q->
}