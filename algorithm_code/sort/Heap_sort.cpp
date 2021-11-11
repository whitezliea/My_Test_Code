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


void sift(int a[],int low ,int high)
{
    int i= low, j = 2*i; // a[j] is left son of a[i]
    int temp = a[i];
    while (j<=high)
    {
        if (j<high&&a[j]<a[j+1]){
            j++;
        }
        if (temp<a[j]){
            a[i] = a[j];
            i=j;
            j=2*i;
        }
        else
        {
            break;
        }
        
    } 
    a[i] = temp;
}
void HeapSort(int a[],int n)
{
    int i=0;
    for(i=n/2;i>=0;i--)
    {
        sift(a,i,n); // init heap;
    }
    for(i=n;i>=1;i--)
    {
        swap_sort(a,0,i);
        sift(a,0,i-1);
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
    HeapSort(a,5);
    display(a,6);
}