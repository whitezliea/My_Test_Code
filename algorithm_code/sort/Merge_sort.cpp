#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;



void merge_(int a[],int L,int M,int R)
{
    int *p = new int[R-L+1];
    int i=0;   
    int p1 = L;
    int p2 = M+1;
    while (p1<=M && p2<=R)
    {
        p[i++] = a[p1] <= a[p2] ? a[p1++]:a[p2++];
    }
    while (p1<=M)
    {
        p[i++]=a[p1++];
    }
    while (p2<=R)
    {
        p[i++] = a[p2++];
    }
    for (int j=0;j<i;j++)
    {
        a[L+j] = p[j];
    }
    
    
    delete []p;
}
void  merge_sort(int a[],int L,int R)
{
     if (L==R){
         return ;
     }
     int mid = L+(R-L)/2;
     merge_sort(a,L,mid);
     merge_sort(a,mid+1,R);
     merge_(a,L,mid,R);
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
    merge_sort(a,0,6);
    display(a,6);
}