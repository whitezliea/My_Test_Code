/*
给定一个包含非负整数的 m x n 网格，
请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
*/
//dp[i][j] = min(dp[i-1][j],dp[i][j-1])+array[i][j] //arr[i][j] 表示网格种的值
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int min(int a,int b)
{
    return a>b?b:a;
}
int shortest_path(int **a,int n, int m)
{
    
    cout<<n<<m<<endl;


    if(m<=0&&n<=0)
    {
        return 0;
    }
    int dp[m][n]={0};
    dp[0][0]=a[0][0];
    //初始化
    for(int i = 1;i<m;i++)
        dp[i][0]=dp[i-1][0]+a[i][0];
    for(int i=1;i<n;i++)
        dp[0][i]=dp[0][i-1]+a[0][i];
    
    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            dp[i][j]  = min(dp[i-1][j],dp[i][j-1])+a[i][j];
    
    return dp[m-1][n-1];
}

int main()
{
//  int arr[][3] = {
//   {1,3,1},
//   {1,5,1},
//   {4,2,1}
//  };
    int m,n;
    cin>>m>>n;
    int arr[m][n]={0};
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
           cin>>arr[i][j];
    int *a[n];
    for(int i=0;i<n;i++)
       a[i]=arr[i];
    int A = sizeof(arr[0])/sizeof(int); //高度
    int B = (sizeof(arr)/sizeof(int))/n ;//长度
    cout<<A<<B<<endl;
    cout<<shortest_path(a,A,B)<<endl;


   
    return 0;
}
/*
1 3 1
1 5 1
4 2 1
*/