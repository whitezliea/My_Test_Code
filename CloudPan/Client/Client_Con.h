//
// Created by white on 11/1/21.
//

#ifndef CLOUDPAN_CLIENT_CON_H
#define CLOUDPAN_CLIENT_CON_H
#include "../public.h"

class Client_Con
{
public:
    Client_Con(int port,const char *addr);
    ~Client_Con();
    void Run();
    void Cloud_Pan_Login();
    void Cloud_Pan_Function();
    void do_Work();
    void sendMsg();
    void getInfo();

private:
    int sock;
    int port;
    const char *m_Addr;
    string msg;
    struct  sockaddr_in Ser_Addr;  /* Structure describing an Internet socket address.  */
};

#endif //CLOUDPAN_CLIENT_CON_H
