//
// Created by white on 11/1/21.
//

#include "Server_Con.h"
#include "Mcache.h"

Server_Con::Server_Con(int port,const char*addr)
{
    if( (listenfd=socket(PF_INET,SOCK_STREAM,0)) <0 ){
        ERR_EXIT("socket");
    }
    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(port);
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);
}

Server_Con::~Server_Con()
{
    //delete db;
}

void Server_Con::Ser_Socket()
{
    int on =1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){
        ERR_EXIT("setsockopt");
    }
}

void Server_Con::Ser_Bind()
{
    if(::bind(listenfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0)  {
        ERR_EXIT("bind");
    }
}


void Server_Con::Ser_Listen()
{
    if (listen(listenfd,SOMAXCONN)<0){  //#define SOMAXCONN	128
        ERR_EXIT("listen");
    }
}

//epoll_work
void Server_Con::ser_epoll_work()
{
    struct epoll_event ev,events[EPOLL_SIZE];
    int epfd = epoll_create(EPOLL_SIZE);
    ev.events = EPOLLIN;
    ev.data.fd =listenfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);

    while(1)
    {
        int events_count = epoll_wait(epfd,events,EPOLL_SIZE,-1); //block event nums
        int i = 0;
        for( ;i<events_count;++i){
            if(events[i].data.fd == listenfd){
                int conn;
                socklen_t peerlen = sizeof(peer_addr);
                pid_t pid;

                system("clear");
                while((conn=accept(listenfd,(struct sockaddr*)&peer_addr,&peerlen))>0)
                {
                    cout<<endl<<"=============== Service ================"<<endl;
                    cout<<" EPOLL:Received New Connection Request "<<endl;
                    cout<<"  connected_fd="<<conn;
                    cout<<"  ip="<<inet_ntoa(peer_addr.sin_addr);
                    cout<<"  port="<<ntohs(peer_addr.sin_port)<<endl;
                    cout<<"========================================"<<endl;
                    
                    pid = fork();   //multi process.
                    if (pid==-1){
                        ERR_EXIT("fork");
                    }

                    if (pid ==0 ){  //son process 
                        close(listenfd); //close listen
                        cout<<"Start do_service"<<endl;

                        do_service(conn);

                        cout<<"End of do_service"<<endl;
                        cout<<"========================================"<<endl;
                        exit(EXIT_SUCCESS);
                    }
                    else{
                        close(conn);  //close connection when return father process 
                    }


                }

            }
        }
    }
}

void Server_Con::do_service(int conn)
{
    while(1)
    {
        int ret = read(conn,(void *)msg.c_str(),1024);
        get_cmd();
        write(conn,(void*)msg.c_str(),msg.size());
        if (ret != -1){
            break;
        }
    }
}

void Server_Con::Ser_Run()
{
    Ser_Socket();
    Ser_Bind();
    Ser_Listen();
    ser_epoll_work();
}


void Server_Con::Select_FTServer()
{
    string FTS_IP =SER_ADDR;
    int FTS_PORT = Transport_Port;
    stringstream ss;
    string port;
    ss<<FTS_PORT;
    ss>>port;
    msg += FTS_IP + " "+port;
}

void Server_Con::get_cmd()
{
    char *ptr = (char*)msg.c_str();
    char *cmd = strtok(ptr, " ");
    string sqlExec;
    int select;
    while(ptr=strtok(NULL," "))  //Still use the last position
    {
        cout<<"ptr = "<<ptr<<endl;
        sql.push_back(ptr);
    }
    
    MyDB *db = new MyDB();
    if(!db->initDB(SER_ADDR,DB_USER,DB_PASSWD,DB_NAME)){
        msg = "ser errpr(myqsl connection)";
        select = -1;
    }
    else{
        select = atoi(cmd); /* Convert a string to an integer.  */
    }

    string user_id = *(sql.begin());
    sql.pop_front();
    string user_passwd = *(sql.begin());
    sql.pop_front();

    Mcache mem(SER_ADDR,MemCache_Port);

    switch (select)
    {
    case ENTER:
        if (strncmp(mem.getValue(user_id.c_str()),user_passwd.c_str(),32)==0){
            msg = "1";
        }
        else{
            msg = "user_id or password is incorrect";
        }
        break;
    
    case REGISTER:
        sqlExec = "select exists (select * from user where user_id ='"+user_id+"');"; //if exits ,return 1
        db->execSQL(sqlExec);
        msg=*(db->getResult()).begin();
        if (strncmp("1",msg.c_str(),1)==0){
            msg = "The user existed!";
        }
        else{
            sqlExec = "insert into user(user_id,password) select '"+user_id+"'," + user_passwd +
             "'from dual where not exists(select *from user where user.user_id='"+user_id+"');";
             db->execSQL(sqlExec);
             msg = "register success!";
        }

        //insert to memcached
        mem.insertValue(user_id.c_str(),user_passwd.c_str(),180);
        break;
    
    case UPLOAD:
        msg ="3 ";
        Select_FTServer();
        break;

    case DOWNLOAD:
        msg="4 ";
        Select_FTServer();
        break;

    default:
        break;
    }
}

int main()
{
    Server_Con ser(Manager_Port,SER_ADDR);
    ser.Ser_Run();
    return 0;
}