//题意：给出一个国际棋盘的大小，判断马能否不重复的走过所有格，并记录下其中按字典序排列的第一种路径。

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

const int N = 35;
int vis[N][N];
int p,q,flag;
int dir[2][8]=
           {
               {-2,-2,-1,-1,1,1,2,2},
               {-1,1,-1,2,-2,2,-1,1}
           };
struct Node
{
    int x;
    int y;
}mp[100];

void dfs(int x,int y,int step,int t)
{
    if(flag) //flag = 1 就返回 说明找到了
     return ;
    vis[x][y] = 1;
    mp[step].x=x;
    mp[step].y=y;
    if(step==p*q&&flag==0)
    {
        flag =1;
        cout<<"Scenario #"<<t<<endl;
        for(int i = 1;i<=step;i++)
        {
            char c = mp[i].x-1+'A';
            cout<<c<<mp[i].y<<" ";
        }
        cout<<endl<<endl; 
        return ;
    }
    for(int i =0;i<8;i++)
    {
        int nx = x + dir[0][i];
        int ny = y + dir[1][i];
        if (!vis[nx][ny] && nx>=1 && nx<=q && ny>=1 && ny<=p)
        {
            dfs(nx,ny,step+1,t);
        }
    }
    vis[x][y]=0; //回溯算法
}

int main()
{
    int T;cin>>T;
    for(int i =1;i<=T;i++)
    {
        cin>>p>>q;
        vis[N][N]={0};
        flag=0;
        dfs(1,1,1,i);
        if(!flag)
        {
            cout<<"Scenario #:"<<i<<endl<<"impossible"<<endl<<endl;
        }
    }
    return 0;
}