/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
问总共有多少条不同的路径？
*/
//dp[i][j];
//dp[i][j]=dp[i-1][j]+dp[i][j-1];
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int path_sum(int m,int n)
{
    if (m<=0||n<=0)
    {
        return 0;
    }
    int dp[m][n]={0};
    //初始化
    for(int i =0;i<m;i++)
    {
        dp[i][0]=1;
    }
    for(int i=0;i<n;i++)
    {
        dp[0][i]=1;
    }
    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
    
    return dp[m-1][n-1];
}

int main()
{
    int m,n;
    cin>>m>>n;
    cout<<path_sum(m,n)<<endl;
    return 0;
}