//
// Created by white on 11/1/21.
//

#ifndef CLOUDPAN_SERVER_CON_H
#define CLOUDPAN_SERVER_CON_H
#include"../public.h"
#include"MyDB.h"
#include"sqlConnPool.h"


class Server_Con 
{
public:
    Server_Con(int port ,const char *addr);
    ~Server_Con();
    void Ser_Socket();
    void Ser_Bind();
    void Ser_Listen();
    int ser_accpet_timeout(unsigned int wait_seconds); //select epoll
    void ser_epoll_work();
    void Ser_Run();

private:
    void Select_FTServer();
    void do_service(int conn);
    void get_cmd();
    
    int listenfd;
    int port;
    char *addr;
    list<string> sql;
    string msg;
    struct sockaddr_in ser_addr,peer_addr;

};


#endif //CLOUDPAN_SERVER_CON_H
