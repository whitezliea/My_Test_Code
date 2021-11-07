//
// Created by white on 11/1/21.
//


#ifndef CLOUDPAN_LOGIN_H
#define CLOUDPAN_LOGIN_H


#include<list>
#include"string.h"
#include"../public.h"


list<string> msg;
string user_name;
string passwd;

enum OP_TYPE{ENTER=1,REGISTER=2,UPLOAD=3,DOWNLOAD=4,SYNC_WRITE=5};

void Cloud_Pan_Login()
{
    cout<<"================================"<<endl;
    cout<<"=  Welcome To My Network Disk  ="<<endl;
    cout<<"================================"<<endl;
    cout<<"=                              ="<<endl;
    cout<<"=      1.Login  2.Register     ="<<endl;
    cout<<"=                              ="<<endl;
    cout<<"================================"<<endl;
    cout<<"Please Input Your Choice:";
}

void Cloud_Pan_Function()
{
    cout<<"================================"<<endl;
    cout<<"=  Welcome To My Network Disk  ="<<endl;
    cout<<"================================"<<endl;
    cout<<"=                              ="<<endl;
    cout<<"=  1.Trans_File  2.Sync_Write  ="<<endl;
    cout<<"=                              ="<<endl;
    cout<<"================================"<<endl;
    cout<<"Please Input Your Choice:";
}

void do_work()
{
    int select=0;
    cin>>select;
    switch (select) {
        case ENTER:
            cout<<"user_name: ";
            cin>>user_name;
            cout<<"password:";
            cin>>passwd;
            msg.push_back("ENTER");
            msg.push_back(user_name);
            msg.push_back(passwd);
            //send();
            break;

        case REGISTER:
            cout<<"user_name: ";
            cin>>user_name;
            cout<<"password:";
            cin>>passwd;
            msg.push_back("REGISTER");
            msg.push_back(user_name);
            msg.push_back(passwd);
            //send();
            break;

        case UPLOAD:
            break;

        case DOWNLOAD:
            break;

        case SYNC_WRITE:
            break;
    }
}

#endif //CLOUDPAN_LOGIN_H
