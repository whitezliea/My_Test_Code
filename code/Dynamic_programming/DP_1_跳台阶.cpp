/*
问题描述：一只青蛙一次可以跳上1级台阶，也可以跳上2级。
求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/
//dp[n]=dp[n-1]+dp[n-2]
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int f(int n)
{
    if (n<=2)
    return n;
    int dp[n+1]={0};
    dp[0] = 1;
    dp[1] = 1;
    //dp[2] = 2;
    for (int i = 2;i<n+1;i++ )
    {
        dp[i] = dp[i-1]+dp[i-2];
    }

    return dp[n];
}

int main()
{
    int n;
    cin>>n;
    cout<<f(n)<<endl;
    return 0;
}


