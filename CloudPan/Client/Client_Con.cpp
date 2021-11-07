//
// Created by white on 11/1/21.
//
#include "md5.h"
#include "Client_Con.h"
Client_Con::Client_Con(int port, const char *addr) {
    m_Addr = addr;
    /*
     * The value (returned by socket function) is a file descriptor.
     * Return -1  when error.
     */
    if((sock= socket(PF_INET,SOCK_STREAM,0)) < 0){     //PF_INET : IPV4_PROTOCOL_FAMILY
        ERR_EXIT("socket");
    }
    memset(&Ser_Addr,0,sizeof(Ser_Addr));
    Ser_Addr.sin_family = AF_INET;
    Ser_Addr.sin_port = htons(port);  //host byte--->network byte long
    Ser_Addr.sin_addr.s_addr = inet_addr(m_Addr);
    cout<<"Client Connect Success!"<<endl;
}

Client_Con::~Client_Con() {}

void Client_Con::Run() {
    if(connect(sock,(struct sockaddr*)&Ser_Addr,sizeof(Ser_Addr)) < 0)
    {
        ERR_EXIT("connect");
    }
    Cloud_Pan_Login();
    while(1)
    {
        do_Work();
        //break;
    }
}

void Client_Con::Cloud_Pan_Login()
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

void Client_Con::Cloud_Pan_Function()
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

void Client_Con::sendMsg() {
    while(1)
    {
        int res = send(sock,msg.c_str(),msg.size()+1,0);
        cout<<"res="<<res<<endl;
        recv(sock,(void *)msg.c_str(),msg.size(),0); //void* : Untyped pointer
        cout<<"recv msg:"<<msg.c_str()<<endl;
        if(strncmp("1",msg.c_str(),1)==0||
                strncmp("register success!",msg.c_str(),10)==0)  //strncmp(v1,v2,1), if v1 == v2 , return 0
        {
            Cloud_Pan_Function();
            do_Work();
        }
        else if(strncmp("The user existed",msg.c_str(),17)==0)
        {
            cout<<msg.c_str()<<endl;
            do_Work();
        }
        else
        {
            system("clear");
            cout<<"User name or password is incorrect!"<<endl;
            do_Work();
        }
        //while(1){}  --- ?
        //break;
    }
}

void Client_Con::getInfo() {
    string user,passwd;
    cout<<"user_name: ";
    cin>>user;
    msg +=user;
    cout<<"password: ";
    msg = msg + " " +MD5(passwd).toString();
    cout<<"send msg="<<msg<<endl;
    sendMsg();
}

void Client_Con::do_Work() {
    int select=0;
    system("clear");
    //Cloud_Pan_Login();
    cin>>select;

    switch (select) {
        case ENTER:
            msg = "1 ";
            getInfo();
            break;

        case REGISTER:
            msg = "2 ";
            getInfo();
            break;

        case UPLOAD:
            msg="3 ";
            break;

        case DOWNLOAD:
            msg ="4 ";
            break;

        case SYNC_WRITE:
            msg = "5 ";
            break;

        default:
            msg="-1 ";
            break;
    }
}

int main()
{
    Client_Con cli(Manager_Port,"127.0.0.1");
    cli.Run();
    return 0;
}