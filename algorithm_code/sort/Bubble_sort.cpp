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

void bubble_sort(int a[],int n)
{
    for (int i = n-1;i>=0;i--){ 

        for(int j=0;j<i;j++){    //min -> max
            if (a[j]>a[j+1]){
                swap_sort(a,j+1,j);
            }
        }
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
    bubble_sort(a,6);
    display(a,6);
}