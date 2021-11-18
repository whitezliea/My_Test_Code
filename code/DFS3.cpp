//要求：给定n个整数，要求选出K个数，使得选出来的K个数的和为sum
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int a[40];
int n,k,sum,ans; // 
bool xuan[40];

void dfs(int cnt,int s,int pos) 
{
    //可行性剪枝
    if (cnt > k || s > sum) {
    
		return;
	}
    if (cnt == k && s ==sum) //
    {
        ans++;
    }
    for(int i =pos;i<n;++i) //pos用来定位当前所遍历数的位置
    {
        if(!xuan[i])
        {
            xuan[i] = 1; //表示此数已被遍历过
            dfs(cnt+1,s+a[i],i+1);
            xuan[i] = 0; //回溯
        }
    }
}

int main()
{
    cin >> n >> k >> sum;
	for (int i = 0; i < n; ++i) {
    
		cin >> a[i];
	}
	ans = 0;
	dfs(0, 0,0);
	cout << ans << endl;
	return 0;
}