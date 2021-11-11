#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

void swap_sort(int a[],int m,int n)
{
    int temp = a[m];
    a[m] = a[n];
    a[n] = temp; 
}

int  partition(int a[],int L,int R)
{
    int i = L; // < area right edge
    int j = R;  // > area left edg
    int temp = a[i];
    while (i<j) //when i==j , break
    {
        while (j>i && a[j] >= temp) //left --> rightf
        {
            j--;
        }
        a[i] = a[j];
        while(i<j&&a[i]<= temp) //left <-- right 
        {
            i++;
        }
        a[j] = a[i];
        
    }
    a[i] = temp;
    return i;
 
    
} 

void quick_sort(int a[],int L, int R)
{
     if(L<R){
        int  p =  partition(a,L,R);
        quick_sort(a,L,p-1);  // < area
        quick_sort(a,p+1,R);  // > area
     }
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
    quick_sort(a,0,5);
    display(a,6);
}