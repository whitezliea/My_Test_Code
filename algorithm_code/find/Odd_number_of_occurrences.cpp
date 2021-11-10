#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;



void pirntOddTimesNum1(int a[],int length)
{
    int eor =0;
    //cout<<sizeof(a)/sizeof(*a)<<endl;
    for (int i=0;i<length;i++){
        eor ^= a[i];
    }
    cout<<"eor is "<<eor<<endl;
}
void pirntOddTimesNum2(int a[],int length)
{
    int eor =0 ,Onlyone =0; 
    //cout<<sizeof(a)/sizeof(*a)<<endl;
    for (int i=0;i<length;i++){
        eor ^= a[i];
    }
    //cout<<"eor is "<<eor<<endl;
    int rightOne = eor & (~eor + 1); //get the rightest 1
    for (int i=0;i<length;i++){
        if ((a[i]&rightOne)==0)
        Onlyone ^= a[i];
    }
    cout<<"eor is "<<Onlyone<<" "<<(eor^Onlyone)<<endl;

}

int main()
{
    int a[]={6,6,5,5,4,4,2,2,3,3,1,1,1};
    int length = sizeof(a)/sizeof(a[0]);
    pirntOddTimesNum1(a,length);
    int b[]={6,6,5,5,4,4,2,2,3,3,1,1,1,7,7,7};
    length = sizeof(b)/sizeof(b[0]);
    pirntOddTimesNum2(b,length);
}