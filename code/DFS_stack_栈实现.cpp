//DFS的栈实现其实是非递归形式
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int n,m;
//int maze[5][5]; //迷宫

int maze[8][8] = 
    {
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,1,0},
        {0,0,0,1,0,0,0,0},
        {1,1,0,1,0,1,1,0},
        {0,0,0,1,0,0,1,1},
        {0,0,1,1,0,0,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,0},
    };
bool visted[8][8]; //记录走过痕迹
int dy[4]={1,-1,0,0}; //上下方向
int dx[4]={0,0,1,-1}; //左右方向
int ans = 9999; //初始化最短步数
int ex, ey; //终点

//定义栈及其用法
struct Stack
{
    int a[10]; //存储栈元素
    int top;
};
typedef struct Stack stack;

typedef struct Node
{
    int x;
    int y;
    int step;
}node ;


void addStack(stack *s, int data) //入栈
{
    s->top++;
    //cout<<s->top<<endl;
    s->a[s->top] = data;
    
}

void delStack(stack *s) //出栈
{
    if(s->top!=-1)
       s->top--;
    else
       cout<<"empty stack"<<endl;
}

int getTop(stack *s) //获得栈顶元素
{
    return s->a[s->top];
}

void print_stack(stack *s)
{
    int t =s->top;
    cout<<"stack :";
    while(t!=-1)
    {
        cout<<s->a[t]<<" ";
        t--;
    }
    cout<<endl;
}

void dfs();

int main()
{
    stack *s =(stack *)malloc(sizeof(stack));
    s->top = -1;
    //cout<<s->top;
    addStack(s,10);
    addStack(s,20);
    addStack(s,30);
    cout<<"getTop is :"<<getTop(s)<<endl;
    addStack(s,40);
    print_stack(s);
    delStack(s);
    print_stack(s);
    return 0;
}