//队列C语言实现
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define MAXSIZE 10 //存储数据元素的最大个数
#define ERROR -99 //ElementType的特殊值，标志错误

struct Node
{
    int x,y;
    int prex,prey;
    int step;
}maze[100][100];


typedef struct Queue
{
    struct Node data[MAXSIZE];
    int front; //记录队列头部
    int rear;  //记录队列尾部
    int size;  //存储数据元素个数
}queue;

int a[100][100],v[100][100];
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};
int n,m,sx,sy,ex,ey;

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

void addQueue(queue *q, Node a)
{
    if(isFullQ(q))
    {
        cout<<"队列已满"<<endl;
        return ;
    }
    q->rear++;
    q->rear %= MAXSIZE;
    q->size++;
    //q->data[q->rear] = data;
    q->data[q->rear] = a;
}

bool isEmpty(queue *q)
{
    return (q->size==0);
}

Node DeleteQ(queue *q)
{
    if(isEmpty(q))
    {
        cout<<"空队列"<<endl;
        exit(0);
    }
    q->front++;
    q->front%=MAXSIZE;
    q->size--;
    return q->data[q->front]; //返回队列头部元素
}

void PrintQueue(queue *q)
{
    if(isEmpty(q))
    {
        cout<<"空队列"<<endl;
        return ;
    }
    cout<<endl;
    cout<<"队首到队尾-打印队列数据元素："<<endl;
    int index = q->front;
    for (int i =0;i<q->size;i++)
    {
        index++;
        index %= MAXSIZE;
        cout<<q->data[index].x<<endl;
        cout<<q->data[index].y<<endl;
        cout<<q->data[index].step<<endl;
    }
    cout<<endl;
}

int main()
{
    queue * q = CreateQueue();
    maze[0][0].x=1;
    maze[0][0].y=2;
    maze[0][0].step=3; 
    addQueue(q, maze[0][0]);

    PrintQueue(q);
    
    DeleteQ(q);

    PrintQueue(q);
    

 
    return 0;

}