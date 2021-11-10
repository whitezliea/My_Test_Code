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

void select_sort(int a[],int n)
{
    //min --> max 
    
    for (int i = n-1;i>=0;i--){ 
        int maxindex = i;
        for (int j=0;j<=i;j++){
            maxindex = a[maxindex] > a[j] ? maxindex : j;
        }
        swap_sort(a,maxindex,i);
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
    select_sort(a,6);
    display(a,6);
}