/*
    Reference URL:
    https://www.cnblogs.com/alantu2018/p/8612722.html
*/
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

void select_test(int conn)
{
    int ret =0;
    fd_set rest;
    FD_ZERO(&rest);
    int _event_wait_nums;
    int max_fd = conn;
    int fd_stdin = fileno(stdin);

    if (fd_stdin > max_fd ){
        max_fd = fd_stdin;
    }
    int len = 0;
    char readbuf[1024]={0};
    char writebuf[1024]={0};
    while(1)
    {
        FD_ZERO(&rest);
        FD_SET(fd_stdin,&rest);
        FD_SET(conn,&rest);
        _event_wait_nums = select(max_fd+1,&rest,NULL,NULL,NULL);

        if(_event_wait_nums == -1){
            perror("select");
            exit(0);
        }
        else if(_event_wait_nums == 0){
            continue;
        }
        if(FD_ISSET(conn,&rest)){
            ret = read(conn,readbuf,sizeof(readbuf));
            if(ret==0){
                printf("server close1\n");
                break;
            }
            else if(-1 == ret){
                perror("read1");
            }
            fputs(readbuf,stdout);
            memset(readbuf,0,sizeof(readbuf));
        }
        
        if(FD_ISSET(fd_stdin,&rest)){
            read(fd_stdin,writebuf,sizeof(writebuf));
            len = strlen(writebuf);
            ret = write(conn, writebuf, len);
            if(ret == 0){
                 printf("server close3\n");
                 break;
            }
            else if( -1 == ret){
                perror("write1");
                break;
            }
            memset(writebuf,0,sizeof(writebuf));
        }
    }
}

int sockfd =0;
int main(int argc ,char **argv)
{
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("socket");
        return -1;
    }

    unsigned short sport = 8080;
    if(argc == 2 ){
        sport = atoi(argv[1]);
    }

    struct sockaddr_in cli_addr;
    cli_addr.sin_family = AF_INET;
    printf("port = %d \n",sport);
    cli_addr.sin_port = htons(sport);
    cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd,(struct sockaddr*)&cli_addr,sizeof(cli_addr))<0){
        perror("connect");
        return -2;
    }

    struct sockaddr_in cli_addr2;
    socklen_t len = sizeof(cli_addr2);
    if(getpeername(sockfd,(struct sockaddr*)&cli_addr2,&len)<0){
        perror("getsockname");
        return -3;
    }

    printf("Server: port:%d, ip: %s\n",ntohs(cli_addr2.sin_port),inet_ntoa(cli_addr2.sin_addr));
    select_test(sockfd);
    close(sockfd);
    return 0;
}