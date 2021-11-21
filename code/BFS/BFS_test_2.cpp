#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
using namespace std;
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

void bfs(int sx,int sy,int ex,int ey)
{
    queue<Node> q;
    q.push(maze[0][0]);
    maze[0][0].x=sx;
    maze[0][0].y=sy;
    maze[0][0].step=0;
    v[sx][sy]=1; //设置为已访问
    bool flag = false;
    while (!q.empty())
    {
        Node temp = q.front();
        int bx = temp.x;
        int by = temp.y;
        int dstep = temp.step;
        if ( bx== ex && by ==ey) //到达终点
        {
            flag = true;
            cout<<flag<<endl;
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
                q.push(maze[tx][ty]);

            }                        
        }
        q.pop();
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