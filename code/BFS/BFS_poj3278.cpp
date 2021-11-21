//题意：就是给出a和b点的横坐标，求到a，b的最小行动次数，
//每次可以向左或向右移动一步，即横坐标加1或者减1，也可以横坐标变成原来的两倍。
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define MAXN 100000
#define MAXSIZE 10000
int N,K;
int vis[MAXN+1]={0};

struct node
{
    int p;
    int time;
};

class Queue
{
public:
    struct node data[MAXSIZE];
    int front; //队首指针
    int rear;  //队尾指针
    int size; //队列大小
public:
    void addQueue(node a);
    node delQueue();
    node getFront();
    bool isEmpty();
    bool isFull();
};

void Queue::addQueue(node a)
{
    if(isFull())
    {
        cout<<"队列已满"<<endl;
        return ;
    }
    rear ++ ;
    rear = rear % MAXSIZE;
    data[rear] = a;
    size++;
}

node Queue::delQueue()
{
    if(isEmpty())
    {
        cout<<"队列空"<<endl;
        exit(0);
    }
    front++;
    front = front % MAXSIZE;
    size--;
    return data[front];// 出队的队首数据
}

node Queue::getFront()
{
    int t = front +1 ;
    return data[t];
}

bool Queue::isEmpty()
{
    return size==0;
}

bool Queue::isFull()
{
    return size==MAXSIZE;
}

Queue q;

void BFS()
{
    node temp = {N,0};
    q.addQueue(temp);
    vis[N]=1;
    while (!q.isEmpty())
    {
        int a = q.getFront().p;
        int b = q.getFront().time;
        q.delQueue();
        if (a==K)
        {
            cout<<b<<endl;
            return ;
        }
        if(a+1<MAXN&&vis[a+1]==0)
        {
            temp.p=a+1;
            temp.time=b+1;
            q.addQueue(temp);
            vis[a+1]=1;
        }
        if(a-1>=0&&vis[a-1]==0)
        {
            temp.p=a-1;
            temp.time=b+1;
            q.addQueue(temp);
            vis[a-1]=1;
        }
        if(a*2<MAXN&&vis[a*2]==0)
        {
            temp.p=a*2;
            temp.time=b+1;
            q.addQueue(temp);
            vis[a*2]=1;
        }

    }
    
}

int main()
{
    cin>>N>>K;
    BFS();
    return 0;
}



