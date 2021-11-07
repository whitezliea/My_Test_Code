#ifndef _CLOUDPAN_FILETRANS_H
#define _CLOUDPAN_FILETRANS_H

#include"../public.h"

class fileTrans
{
private:
    int trans_fd;
    int connfd;
    string user_id;
    string msg;
    list<string> sql;
    struct fileInfo m_fileinfo_;
    struct fileData m_filedata_;
    struct sockaddr_in seraddr,peeraddr;

private:
    bool sendFile();
    bool recvFile();
    bool createFile();
    bool removeFile(string path);
    void sendFileInfo();
    void getFileInfo();
    void showFileList();
    void getCmd();

public:
    fileTrans(int port,const char*addr);
    ~fileTrans();
    void Run();
};



#endif