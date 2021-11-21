//可行性剪枝
//要求：给定n个整数，要求选出K个数，使得选出来的K个数的和为sum
#include<iostream>
#include<stdio.h>
using namespace std;
int a[40];
int n,k,sum,ans;
//cnt为选择的个数
void dfs(int i,int cnt,int s)
{
    //可行性剪枝
    if(cnt>k) //选择的个数大于给定的时候，进行剪枝
    {
        return ;
    }
    if(s>sum) //求和大于sum是，进行剪枝
    {
        return ;
    }
    if(i==n) //遍历到数组最后一位
    {
        if(cnt==k&&s==sum)
        {
            ans++;
        }
        return ;
    }
    dfs (i+1,cnt,s);//不选该数,同时下一位
    dfs (i+1,cnt+1,s+a[i]);//选择该数，同时下一位

}

int main()
{
    cin>>n>>k>>sum;
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
    }
    ans =0;
    dfs(0,0,0);
    cout<<ans<<endl;
    return 0;
}