#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>

using namespace std;

struct CacheData
{
    int id;
    string data;
};

queue<CacheData> Q;
const int MAX_CACHEDATA_LENGTH =10;

mutex m;
condition_variable condConsumer;
condition_variable condProductor;

int ID = 1;

void ConsumerActor()
{
    unique_lock<mutex> lockerConsumer(m);
    cout<<"["<<this_thread::get_id()<<" ] get lock"<<endl;
    while(Q.empty())
    {
        cout<<"due to queue is empty, consumer sleep."<<endl;
        cout<<"["<<this_thread::get_id()<<"] donnot have lock"<<endl;
        condConsumer.wait(lockerConsumer);
        cout<<"["<<this_thread::get_id()<<"] weak, get the lock again."<<endl;
    } 
    cout<<"["<<this_thread::get_id()<<"] "<<endl;
    CacheData temp = Q.front();
    cout<<"- ID:"<<temp.id<<" Data:"<<temp.data<<endl;
    Q.pop();
    condProductor.notify_one();
    cout<<"["<<this_thread::get_id()<<"] freed the lock"<<endl;
}

void ProducerActor()
{
    unique_lock<mutex> lockerProducer(m);
    cout<<"["<<this_thread::get_id()<<" ] get lock"<<endl;
    while(Q.size()>MAX_CACHEDATA_LENGTH)
    {
        cout<<"due to queue is full, producer sleep."<<endl;
        cout<<"["<<this_thread::get_id()<<"] donnot have lock"<<endl;
        condProductor.wait(lockerProducer);
        cout<<"["<<this_thread::get_id()<<"] weak, get the lock again."<<endl;
    } 
    cout<<"["<<this_thread::get_id()<<"] "<<endl;
    CacheData temp;
    temp.id=ID++;
    temp.data="*****";
    cout<<"+ ID"<<temp.id<<" Data: "<<temp.data<<endl;
    Q.push(temp);
    condConsumer.notify_one();
    cout<<"["<<this_thread::get_id()<<"] freed the lock"<<endl;
}


void ConsumerTask()
{
    while(1)
    {
        ConsumerActor();
    }
}

void ProducerTask()
{
    while(1)
    {
        ProducerActor();
    }
}

void Dispath(int ConsumerNum, int ProducerNum)
{
    vector<thread> thsC;
    for (int i = 0;i<ConsumerNum;++i){
        thsC.push_back(thread(ConsumerTask));
    }

    vector<thread> thsP;
    for (int j =0;j<ProducerNum;++j){
        thsP.push_back(thread(ProducerTask));
    }

    for (int i = 0; i < ConsumerNum; ++i){
		if (thsC[i].joinable()){
			thsC[i].join();
		}
	}
	
	for(int j=0;j<ProducerNum;++j){
        if(thsP[j].joinable()){
            thsP[j].join();
        }
    }
}

int main()
{
    Dispath(1,5);
    return 0;
}