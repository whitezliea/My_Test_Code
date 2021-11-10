#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

int merge(int a[],int L, int M ,int R)
{
    int *p = new int[R-L+1];
    int i =0;
    int p1 =L ;
    int p2 = M+1;
    int res =0;
    while (p1<=M&&p2<=R)
    {
        res += a[p1]<a[p2] ?  (R-p2+1)*a[p1] : 0;
        p[i++] = a[p1]<a[p2]  ?a[p1++] : a[p2++];
    }
    while (p1<=M)
    {
        p[i++] = a[p1++];
    }
    while (p2<=R)
    {
        p[i++] = a[p2++];
    }
    for(int j=0;j<i;j++){
        a[L+j] = p[j];
    }
    return res;
    delete []p;

}
int merge_sort(int a[],int L,int R)
{
    if (L==R){
        return 0;
    }
    int mid = L + (R-L)/2;
    return merge_sort(a,L,mid)+merge_sort(a,mid+1,R)+merge(a,L,mid,R);
}

int smallSum(int a[],int length)
{
    if (a==NULL||length<2){
        return 0;
    }
    return merge_sort(a,0,length-1);
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
  int a[5] = {1,3,4,2,5};
  int length = sizeof(a)/sizeof(a[0]);
  cout<<length<<endl;
  
  cout<<"small sum is "<<smallSum(a,length)<<endl;
  display(a,length);
}