#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define MAXSIZE 50


class Queue
{
public:
    int data[MAXSIZE];
    int rear; //队尾指针
    int front; //队首指针
    int size;
public:
    Queue();
    void addQueue(int a); //入队
    int delQueue();//出队
    int getSize(); //获取队长度
    bool isEmpty();
    int getFront(); //获取队首数据
    bool isFull();
    
};

Queue::Queue()
{
    front = -1;
    rear = -1;
    size =0;
}

void Queue::addQueue(int a)
{
    if(isFull())
    {
        cout<<"队列已满"<<endl;
        return ;
    }
    rear ++;
    rear = rear % MAXSIZE;
    data[rear] = a;
    size ++;
}

int Queue::delQueue()
{
    if(isEmpty())
    {
        cout<<"队列为空"<<endl;
        exit(0);
    }
    front++;
    front = front%MAXSIZE;
    size--;
    return data[front]; //这个出队的数据
}

bool Queue::isFull()
{
    return size==MAXSIZE;
}

bool Queue::isEmpty()
{
    return size ==0;
}

int Queue::getFront()
{
    int t = front +1; 
    return data[t];
}

int Queue::getSize()
{
    return size;
}

int main()
{
    Queue q;
    q.addQueue(5);
    q.addQueue(4);
    q.addQueue(3);
    q.addQueue(2);
    q.addQueue(1);
    //tail -->1 2 3 4 5 -->head
    cout<<q.getFront()<<endl; //5
    cout<<q.delQueue()<<endl; //5
    cout<<q.getSize()<<endl; // 4
    cout<<q.getFront()<<endl; // 4
    return 0;
}