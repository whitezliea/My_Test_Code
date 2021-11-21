/*
这个就是定义hang 【num】和列i，然后每一行从第一个位置开始放皇后，
如果可以的话就标记为1，然后接着往下找第二行，也是从第二行第一个位置开始找，
满足接着第三行。当如果发现第三行不能再放置皇后了，这个时候第三行那个位置已经标记为1 ，
所以这个时候就回溯到第二行也就是上一层从新判断同时把标记为1 的变量还原为0，直到满足条件输出。
题中有一个陷阱，深搜的时候是按列输出的，不是行输出。
*/

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int hang[11],n=8;
int a[10][10]={0};
int t =1;

void print()
{
    cout<<"no."<<t++<<endl;
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            cout<<a[j][i]<<" ";
        }
        cout<<endl;
    }
}

bool judge(int num)
{
    for(int i = 1;i<num;i++) //从第一行往上判断是否可以放置皇后
    {
        if(hang[num]==hang[i]||abs(hang[i]-hang[num])==num - i)
            return false;
    }
    return true;
}

void dfs(int num)
{
    if(num>=9)
    {
        print();
        return;
    }
    for(int i=1;i<=8;i++)
    {
        hang[num] = i; //在当前行放置皇后
        if(a[num][i]!=1&&judge(num))
        {
            a[num][i]=1;//当前位置放置皇后
            dfs(num+1);
            a[num][i]=0;//回溯算法
        }
    }
}

int main()
{
    dfs(1);
    return 0;
}