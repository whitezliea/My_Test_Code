#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int find_max(int m, int n)
{
    return m>n?m:n;
    
}

int  recursion_find_max(int a[],int L,int R)
{
    //min --> max 
    if (L==R){
        return a[L];
    }
    int mid = L+(R-L)/2;
    int leftMax = recursion_find_max(a,L,mid);
    int rightMax = recursion_find_max(a,mid+1,R);
    return find_max(leftMax,rightMax);
}
void display(int a[],int n)
{
    cout<<"array is ";
    for(int i=0;i<n;i++){
        cout<<a[i]<< " ";
    }
    cout<<endl;
}



int main()
{
    int a[6]={6,5,4,2,3,1};
    display(a,6);
    int v = recursion_find_max(a,0,6);
    cout<<"max value is " << v<<endl;
    
}