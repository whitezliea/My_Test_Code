#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
//注意队列的长度，若没有空间限制，推荐取大一点
#define MAXSIZE 50 //存储数据元素的最大个数 
int a[100][100],v[100][100];
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};
struct Node
{
    int x,y;
    int prex,prey;
    int step;
}maze[100][100];
int n,m,sx,sy,ex,ey;

class Queue
{
public:
    struct Node data[MAXSIZE];
    int front; //记录队列头部
    int rear;  //记录队列尾部
    int size;  //存储数据元素个数
public:
    Queue(); //构造函数
    bool isFullQ();
    void addQueue(Node a);
    bool isEmpty();
    Node DeleteQ();
    void PrintQueue();
    Node getfornt();
};
Queue::Queue()
{
    front = -1;
    rear = -1;
    size = 0;
}

bool Queue::isFullQ()
{
    return size==MAXSIZE;
}

void Queue::addQueue(Node a)
{
    if(isFullQ())
    {
        cout<<"队列已满"<<endl;
        return ;
    }
    rear++;
    rear %= MAXSIZE;
    size++;
    //q->data[q->rear] = data;
    data[rear] = a;
}

bool Queue::isEmpty()
{
    return size==0;
}

Node Queue::DeleteQ()
{
    if(isEmpty())
    {
        cout<<"空队列"<<endl;
        exit(0);
    }
    front++;
    front%=MAXSIZE;
    size--;
    return data[front]; //返回队列尾部元素
}
Node Queue::getfornt()
{
    int t = front+1;
    return data[t];
}

void Queue::PrintQueue()
{
    if(isEmpty())
    {
        cout<<"空队列"<<endl;
        return ;
    }

    cout<<"队首到队尾-打印队列数据元素："<<endl;
    int index = front;
    for (int i =0;i<size;i++)
    {
        index++;
        index %= MAXSIZE;
        cout<<data[index].x<<endl;
        cout<<data[index].y<<endl;
        cout<<data[index].step<<endl;
    }
    cout<<endl;
}



void bfs(int sx,int sy,int ex,int ey)
{
    Queue q;
    maze[0][0].x=sx;
    maze[0][0].y=sy;
    maze[0][0].step=0;
    q.addQueue(maze[0][0]);

    v[sx][sy]=1; //设置为已访问
    bool flag = false;
    while (!q.isEmpty())
    {
        Node temp = q.getfornt();
        int bx = temp.x;
        int by = temp.y;
        int dstep = temp.step;
        if ( bx== ex && by ==ey) //到达终点
        {
            flag = true;
           // cout<<flag<<endl;
            cout<<"step is "<<dstep<<endl;
            break;
        }
        for (int i =0;i<4;i++)
        {
            int tx=bx+dx[i];
            int ty=by+dy[i];  
            if(tx<0||tx>n-1||ty<0||ty>m-1||v[tx][ty]==1||a[tx][ty]==1)
            {
                continue;
            }         
            if (a[tx][ty]==0&&v[tx][ty]==0)
            {
                v[tx][ty]=1; //设置为已访问
                maze[tx][ty].x=tx;
                maze[tx][ty].y=ty;
                maze[tx][ty].prex=bx;
                maze[tx][ty].prey=by;
                maze[tx][ty].step=dstep+1;
                q.addQueue(maze[tx][ty]);
               // cout<<maze[tx][ty].x<<" "<<maze[tx][ty].y<<endl;

            }                        
        }
        q.DeleteQ();
    }
    if (!flag)
    {
        cout<<"no answer"<<endl;
    }
    return ;

}

void print_path(int x,int y)
{
    if(x==sx&&y == sy)
    {
        cout<<"("<<maze[sx][sy].x<<","<<maze[sx][sy].y<<")"<<endl;
        return ;
    }
    int prex = maze[x][y].prex;
    int prey = maze[x][y].prey;
    print_path(prex,prey);
    cout<<"("<<maze[x][y].x<<","<<maze[x][y].y<<")"<<endl;
}

int main()
{
    cin>>n>>m>>sx>>sy>>ex>>ey;
    cout<<n<<m<<sx<<sy<<ex<<ey<<endl;
    for (int i =0;i<n;i++)
       for(int j =0;j<m;j++)
       {
           cin>>a[i][j];
       }

    bfs(sx,sy,ex,ey);
    print_path(ex,ey);
    return 0;
}

/*
0 0 0 0 0 0 0 0 
0 0 0 1 1 1 1 0 
0 0 0 1 0 0 0 0 
1 1 0 1 0 1 1 0 
0 0 0 1 0 0 1 1 
0 0 1 1 0 0 0 0 
0 0 0 0 0 1 0 0 
0 0 0 0 0 1 0 0 
*/