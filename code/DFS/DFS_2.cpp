//最优性剪枝
//代表：迷宫求最短路径步数问题
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
bool in(int x,int y)  //判断该点是否在地图内
{
    return x>=0&&x<n&&y>=0&&y<m;
}
//dfs

void dfs(int x,int y ,int step)
{
    //最优化剪枝
    if (step>=ans)
    {
        return ;
    }
    if(x == ex&& y ==ey)
    {
        ans = step; //记录当前步数
        return ;
    }
    visted[x][y] = 1; //记录该点为已访问
    //四个方向进行探索
    for(int i=0;i<4;++i)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if(in(tx,ty)&& maze[tx][ty]!= 1 && visted[tx][ty] != 1)
        {
            dfs(tx,ty,step+1);//步数加1
        }
    }
    visted[x][y]=0; //回溯算法


}

int main()
{
    // maze[5][5] = 
    // {
    //     {0,0,0,0,0},
    //     {0,1,0,1,0},
    //     {0,0,0,0,1},
    //     {1,0,1,0,0},
    //     {0,0,0,0,0}
    // };
    n=8,m=8;
    ex=7,ey=7;
    dfs(0,0,0);
    cout<<ans<<endl;
    //return 0;
}