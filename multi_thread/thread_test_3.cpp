#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex m; 

void proc1(int a)
{
    m.lock();
    cout<<"porc 1 is wirting a "<<endl;
    cout<<"before a is "<<a<<endl;
    cout<<"after a is "<<a+2<<endl;
    m.unlock();
}

void proc2(int a)
{
    m.lock();
    cout<<"porc 2 is wirting a "<<endl;
    cout<<"before a is "<<a<<endl;
    cout<<"after a is "<<a+1<<endl;
    m.unlock();
}

int main()
{
    int a = 0;
    thread t1(proc1,a);
    thread t2(proc2,a);
    t1.join();
    t2.join();
    return 0;
}