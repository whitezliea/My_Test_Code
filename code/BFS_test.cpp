#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<queue>
using namespace std;
int a[100][100],v[100][100];
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};
struct point
{
    int x;
    int y;
    int step=0;
};

int n,m,sx,sy,ex,ey;
queue<point> r; //申请队列

void bfs(int sx,int sy,int ex,int ey)
{
    //1、起点入队
    point start;
    start.x = sx;
    start.y = sy;
    r.push(start); //
    v[sx][sy] = 1; //标记为已访问
    bool flag = false;
    while(!r.empty())
    {
        
        int x = r.front().x;
        int y = r.front().y;
        if ( x== ex && y ==ey) //到达终点
        {
            flag = true;
            cout<<flag<<endl;
            cout<<"step is "<<r.front().step<<endl;
            break;
        }
        for (int k=0;k<4;k++)
        {
            int tx=x+dx[k];
            int ty=y+dy[k];
            if(tx<0||tx>n-1||ty<0||ty>m-1||v[tx][ty]==1||a[tx][ty]==1)
            {
                continue;
            }
            if (a[tx][ty]==0&&v[tx][ty]==0)
            {
                point temp;
                temp.x = tx;
                temp.y = ty;
                temp.step = r.front().step+1;
                r.push(temp);
                v[tx][ty]=1;
            }
        }
        r.pop(); //拓展完了，需要将队首元素出队

    }
    if (!flag)
    {
        cout<<"no answer"<<endl;
    }
    return ; 
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