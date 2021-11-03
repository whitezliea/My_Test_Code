/*
    Reference URL: 
    https://www.cnblogs.com/xcywt/p/8146094.html
    
*/

/*
　　 #include <sys/epoll.h>
       int epoll_create(int size);
       int epoll_create1(int flags);
       int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
       int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
       The struct epoll_event is defined as :
           typedef union epoll_data {
               void    *ptr;
               int      fd;
               uint32_t u32;
               uint64_t u64;
           } epoll_data_t;
           struct epoll_event {
               uint32_t     events;    /* Epoll events 
               epoll_data_t data;      //* User data variable 
           };
*/

#include<sys/types.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<poll.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<vector>
#include<algorithm>

void _set_fd_is_block(int fd, bool _is_block)
{
    // https://subingwen.cn/linux/fcntl-dup2/#3-fcntl
    // https://www.cnblogs.com/xuyh/p/3273082.html  -->fcntl
    int flags = fcntl(fd,F_GETFL);  //get file status
    if (flags<0){
        return ;
    }
    if (_is_block) {
        //# define O_NONBLOCK	  04000
        flags &= ~O_NONBLOCK;
    }
    else{
        flags != ~O_NONBLOCK;
    }

    if(fcntl(fd,F_SETFL,flags)<0){
        perror("fcntl set");
    }
    
}

typedef std::vector<struct epoll_event> EventList;
#define CLIENTCOUT 2048
#define MAX_EVENTS 2048

int main(int argc,char **argv)
{
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0){
        perror("socket");
        return -1;
    }

    unsigned short sport =8080;
    if (argc==2){
        sport == atoi(argv[1]);
    }
    struct sockaddr_in ser_addr;
    ser_addr.sin_family=AF_INET;
    printf("port = %d\n",sport);
    ser_addr.sin_port = htons(sport);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(listenfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0){
        perror("bind()");
        return -2;
    }

    if(listen(listenfd,20)<0){
        perror("listen");
        return -3;
    }

    struct sockaddr_in connaddr;
    socklen_t len = sizeof(connaddr);

    int i =0, ret =0;
    std::vector<int> clients; // the itreator saved by client.
    int epollfd = epoll_create1(EPOLL_CLOEXEC);
    // int epollfd = epoll_create(MAX_EVENTS);

    struct epoll_event event;
    event.events = EPOLLIN|EPOLLET;
    event.data.fd = listenfd;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event)<0){
       perror("epoll_ctl");
       return  -2;
    }
    EventList _events(16);
    int count = 0;
    int _events_wait_nums = 0;
    char buf[1024]={0};
    int conn = 0;
    
    while(1){

        _events_wait_nums = epoll_wait(epollfd,&*_events.begin(),static_cast<int>(_events.size()),-1);
        if(_events_wait_nums == -1){
            perror("epoll_wait");
        }
        if(_events_wait_nums == 0){
            continue;
        }
        if((size_t)_events_wait_nums == _events.size()){
            _events.resize(_events.size() * 2);
        }
          
        for(i = 0;i<_events_wait_nums;i++){
            if(_events[i].data.fd == listenfd){
                conn = accept(listenfd,(struct sockaddr*)&connaddr,&len);
                if(conn<0){
                    perror("accpet");
                    return -4;
                }

                char _str_ip[64] ={0};
                char *ip = inet_ntoa(connaddr.sin_addr);
                strcpy(_str_ip,ip);
                printf("client connect , conn: %d,ip: %s, port: %d, count: %d\n",conn ,_str_ip, ntohs(connaddr.sin_port),++count );

                clients.push_back(conn);
                _set_fd_is_block(conn,false); //set block
                event.events = EPOLLIN|EPOLLET;
                epoll_ctl(epollfd,EPOLL_CTL_ADD,conn,&event);

            }
            else if(_events[i].events & EPOLLIN){  //EPOLLIN = 0x001,
                conn = _events[i].data.fd;
                 if (conn<0){
                     continue;
                 }
                 ret = read(conn,buf,sizeof(buf));
                 if(ret == -1){
                     perror("read");
                     return -5;
                 }
                 else if(ret == 0)
                 {
                     printf("client close remove: %d, count: %d\n",conn, --count);
                     close(conn);
                     event = _events[i];
                     epoll_ctl(epollfd,EPOLL_CTL_DEL,conn,&event);

                     clients.erase(std::remove(clients.begin(),clients.end(),conn),clients.end());
                 }

                 write(conn,buf,sizeof(buf));
                 memset(buf,0,sizeof(buf));
            }
        }
    }
    close(listenfd);
    return 0;


}
