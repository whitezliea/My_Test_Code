//
// Created by white on 11/1/21.
/*
 * Filename: public.h
 * Author: whitealiez
 * mail: whitealiez@outlook.com
 */
//

#ifndef CLOUDPAN_PUBLIC_H
#define CLOUDPAN_PUBLIC_H

#include "string"
#include "list"   // list vector
#include "unistd.h"  //access POSIX OS API
#include "arpa/inet.h"  //network function
#include <cstdio>
#include <cstdlib>
#include "sys/epoll.h"  //epoll
#include "sys/stat.h"  //file status
#include "sys/socket.h" //socket
#include "sys/sendfile.h"   // copy data directly from one file descriptor to another
#include "netinet/in.h"  //ip  address family
#include "fcntl.h"    // File Control Operations
#include "cstring"
#include "sstream"  //string stream
#include "iostream"
#include <csignal>  //signal
#include <cerrno>  //Record the last error code of the system , the result is an integer variable.


using namespace std;

//port definition
#define Manager_Port 6666 //
#define Transport_Port 6667 //
#define Rest_Port  6668 //
#define MemCache_Port 11211 //

//Other Information
#define SER_ADDR "127.0.0.1"
#define DB_USER   "root"
#define DB_PASSWD  "root"
#define DB_NAME "CloudPan"

#define SER_HOME_PATH "/home/white/CloudPan/serdir"
#define CLI_HOME_PATH "/home/white/CloudPan/clidir"

#define BUFFSIZE 128

#define ERR_EXIT(m) \
        do          \
        {           \
          perror(m);\
          exit(EXIT_FAILURE);\
        }while(0)  //perror : print the cause of the error

#define EPOLL_SIZE 50

//user operation type
enum OP_TYPE{ERR=-1,ENTER=1,REGISTER=2,UPLOAD=3,DOWNLOAD=4,SYNC_WRITE=5,RM=6,LS=7};

//USER INFORMATION
typedef struct Msg
{
    OP_TYPE op_type;
    string user_id;
    string password;
}msgInfo;  //new name

//File Header Info
struct fileInfo
{
    string file_name;
    string file_md5;
    string file_path;
    int file_size;
    int file_chunk_size;
    int chunk_size_standard;
    bool trans_status;
};

//File Info
struct fileData
{
    string file_name;
    int id;  //chunk id;
    int offset;
    bool trans_status;
};





#endif //CLOUDPAN_PUBLIC_H
