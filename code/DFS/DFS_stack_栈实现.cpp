//DFS的栈实现其实是非递归形式
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int n=8,m=8;
#define MAXSIZE 1000
//int a[5][5]; //迷宫

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
int visted[8][8]; //记录走过痕迹
int dy[4]={1,0,-1,0}; //上下方向
int dx[4]={0,1,0,-1}; //左右方向
int ans = 9999; //初始化最短步数
int ex, ey; //终点

struct Node
{
    int x;
    int y;
    int prex;
    int prey;
    int step;
}a[100][100];


class Stack
{
public:
   struct Node data[MAXSIZE];
   int top; //栈顶
   int size;
public:
   Stack(); //构造函数
   void addStack(Node n);
   Node delStack();
   Node getTop();
   bool isEmpty();
   void printStack();
};

Stack::Stack()
{
    top = -1;
    size = 0;
}

bool Stack::isEmpty()
{
    return size==0;
}

void Stack::addStack(Node n)
{
    top++;
    size++;
    data[top] = n;
}

Node Stack::delStack()
{
    if(isEmpty())
    {
        cout<<"空栈"<<endl;
        exit(0);
    }
    top--;
    size--;
    return data[top];
}

Node Stack::getTop()
{
    return data[top];
}

void Stack::printStack()
{
    if(isEmpty())
    {
        cout<<"空栈"<<endl;
        exit(0);
    }
    int t = top;
    while(t!=-1)
    {
        cout<<data[t].x<<endl;
        t--;
    }
    cout<<endl;
}

bool in(int tx,int ty)
{
   if( tx<0||tx>n-1||ty<0||ty>m-1)
   {
       return true;
   }
   else 
     return false;  

}
int dfs(int sx,int sy,int ex,int ey)
{
    Stack s;
    int minstep = 9999;
    a[0][0].x=sx;
    a[0][0].y=sy;
    a[0][0].step=0;
    s.addStack(a[0][0]);
    visted[sx][sy]=1;
    bool flag = false;
    while(!s.isEmpty())
    {
        Node temp = s.getTop();
        int bx = temp.x;
        int by = temp.y;
        int dstep = temp.step;
        s.delStack(); //出栈 
        for (int i =0;i<4;)
        {
            int tx=bx+dx[i];
            int ty=by+dy[i];  
            // if(tx<0||tx>n-1||ty<0||ty>m-1||visted[tx][ty]==1||maze[tx][ty]==1)
            // {
            //     continue;
            // }         
            if (maze[tx][ty]==0&&visted[tx][ty]==0&&!in(tx,ty))
            {
                a[tx][ty].x=tx;
                a[tx][ty].y=ty;
                a[tx][ty].step=dstep+1;

                a[tx][ty].prex=bx;
                a[tx][ty].prey=by;

                if (tx == ex && ty == ey)
                {
                    flag = true;
                    if (minstep > a[tx][ty].step)
                    {
                        minstep = a[tx][ty].step;
                        cout<<"min:"<<minstep<<endl;
                    }
                    
                }


                visted[tx][ty]=1; //设置为已访问
                s.addStack(a[tx][ty]);
                i=0;
               // break;

            }       
            else i++;
        }

    }
    return minstep;
}

void print_path(int x,int y)
{
    int sx=0,sy=0;
    if(x==sx &&y == sy)
    {
        cout<<"("<<a[sx][sy].x<<","<<a[sx][sy].y<<")"<<endl;
        return ;
    }
    int prex = a[x][y].prex;
    int prey = a[x][y].prey;
    print_path(prex,prey);
    cout<<"("<<a[x][y].x<<","<<a[x][y].y<<")"<<endl;
}


int main()
{
    ans = dfs(0,0,7,7);
    cout<<"ans:"<<ans<<endl;
    print_path(7,7);
    return 0;
}




