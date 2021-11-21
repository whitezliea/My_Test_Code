#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int R,C;
int map[105][105];
int mark[105][105]={0};
int dfs(int i ,int j)
{
    int k=0; //路径长
    if(mark[i][j])
    {
        return mark[i][j];
    }
    if(i!=0&&map[i-1][j]<map[i][j]) //向左走
    {
        k=dfs(i-1,j)+1;
        if(k>mark[i][j])
        {
            mark[i][j]=k;
        }
    }
    if(i!=R-1&&map[i+1][j]<map[i][j])//向右走
    {
        k=dfs(i+1,j)+1;
        if(k>mark[i][j])
        {
            mark[i][j]=k;
        }
    }
    if(j!=0&&map[i][j-1]<map[i][j]) //向上走
    {
        k=dfs(i,j-1)+1;
        if(k>mark[i][j])
        {
            mark[i][j]=k;
        }
    }
    if(j!=C-1&&map[i][j+1]<map[i][j])//向下走
    {
        k=dfs(i,j+1)+1;
        if(k>mark[i][j])
        {
            mark[i][j]=k;
        }
    }
    return mark[i][j];
}

int main()
{
    int i,j,k,sum=0;
    cin>>R>>C;
    for(i=0;i<R;i++)
        for(j=0;j<C;j++)
            cin>>map[i][j];
    for(i=0;i<R;i++)
        for(j=0;j<C;j++)
            {
                k=dfs(i,j); //从每个点开始出发
                if(k>sum)
                    sum=k;
            }
    cout<<sum+1<<endl;
    return 0;
}