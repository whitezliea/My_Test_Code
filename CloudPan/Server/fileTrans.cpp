#include"MyDB.h"
#include"Mcache.h"
#include"md5.h"
#include"fileTrans.h"
#include<string>
#include "sys/stat.h"

fileTrans::fileTrans(int port, const char*addr)
{
    if((trans_fd = socket(PF_INET,SOCK_STREAM,0))<0){
        ERR_EXIT("socket");
    }
    memset(&seraddr,0,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port = htons(port);
    seraddr.sin_addr.s_addr=htonl(INADDR_ANY);

    int on = 1;
    if(setsockopt(trans_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){
        ERR_EXIT("setsockopt");
    }
    if(::bind(trans_fd,(struct sockaddr*)&seraddr,sizeof(seraddr))<0){
        ERR_EXIT("bind");
    }
    if (listen(trans_fd,SOMAXCONN)<0){
        ERR_EXIT("listen");
    }
}

fileTrans::~fileTrans()
{
    close(trans_fd);
    close(connfd);
}

void fileTrans::Run()
{
    struct epoll_event ev,events[EPOLL_SIZE];
    int epfd = epoll_create(EPOLL_SIZE);
    ev.events = EPOLLIN;
    ev.data.fd =trans_fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,trans_fd,&ev);

    while(1)
    {
        //Return the number of file descriptors that are ready on success
        int events_count = epoll_wait(epfd,events,EPOLL_SIZE,-1);
        int i=0;

        for(;i<events_count;++i){
            socklen_t peerlen = sizeof(peeraddr);

            pid_t  pid;

            while((connfd = accept(trans_fd,(struct sockaddr*)&peeraddr,&peerlen)) > 0)
            {
                cout<<"---------FileTrans-Server-----------"<<endl;

                pid = fork();
                if(pid==-1){
                    ERR_EXIT("fileTrans fork");
                }
                if (pid ==0 ){
                    close(trans_fd);
                    cout<<"Start fileTrans server"<<endl;

                    int ret = read(connfd,(void*)msg.c_str(),1024);

                    if(ret == -1){
                        ERR_EXIT("read");
                    }
                    getCmd();

                    write(connfd,(void*)msg.c_str(),1024);
                    cout<<"end of fileTrans server"<<endl;
                    exit(EXIT_SUCCESS);
                }
                else{
                    close(connfd);
                }
            }
        } 
    }

}

void fileTrans::getCmd()
{
    //"OP_TYPE user_id file_name file_MD5 file_path file_size file_chunk_size chunk_size trans_status"
    char *ptr  = (char*)msg.c_str();
    char *cmd = strtok(ptr," ");
    while (ptr=strtok(NULL," "))
    {
        sql.push_back(ptr);
    }
    user_id = *(sql.begin());
    sql.pop_front();
    int select = atoi(cmd);

    switch (select)
    {
    case UPLOAD:
        getFileInfo();
        recvFile();
        break;

    case DOWNLOAD:
        sendFileInfo();
        sendFile();
        break;

    case RM:
        removeFile(m_fileinfo_.file_path);
        break;
    
    case LS:
        showFileList();
        break;

    default:
        break;
    }
}

void fileTrans::getFileInfo()
{
    //"file_name file_MD5 file_path file_size file_chunk_size  trans_status"
    m_fileinfo_.file_name = *(sql.begin());
    sql.pop_front();
    
    //"file_MD5 file_path file_size file_chunk_sizetrans_status"
    m_fileinfo_.file_md5 = *(sql.begin());
    sql.pop_front();
    
    //"file_path file_size file_chunk_size trans_status"
    m_fileinfo_.file_path = *(sql.begin());
    sql.pop_front();
   
    //"file_size file_chunk_size  trans_status"
    const char *cmd = (*(sql.begin())).c_str();
    m_fileinfo_.file_size = atoi(cmd);
    sql.pop_front();

    //"file_chunk_size trans_status"
    cmd = (*(sql.begin())).c_str();
    m_fileinfo_.file_chunk_size = atoi(cmd);
    sql.pop_front();
    
    //" trans_status"
    m_fileinfo_.trans_status = false;

}

void fileTrans::sendFileInfo()
{
    MyDB *db = new MyDB();
    if (!db->initDB(SER_ADDR,DB_USER,DB_PASSWD,DB_NAME)){
        msg = "ser error(mysql connction";
        return ;
    }
    string selectSQL = "select * from files where user_name"+user_id +"and file_path = "+m_fileinfo_.file_path+";";
    db->execSQL(selectSQL);
    sql = db->getResult();

    getFileInfo();

    write(connfd,&m_fileinfo_,sizeof(m_fileinfo_));
}

bool fileTrans::recvFile()
{
    Mcache mem(SER_ADDR,MemCache_Port);
    MyDB *db = new MyDB();
    if(mem.getValue(m_fileinfo_.file_md5.c_str())==NULL){
        if (createFile()==false){
            ERR_EXIT("open file");
        }

        if(strncmp((m_fileinfo_.file_md5).c_str(), (MD5(m_fileinfo_.file_path).toString().c_str()),32)!=0){
            ERR_EXIT("file md5 error");
        }

        m_fileinfo_.trans_status = true;
        mem.insertValue((m_fileinfo_.file_md5).c_str(),(m_fileinfo_.file_name).c_str(),180);

    }

    //insert to mysql 
    if (!db->initDB(SER_ADDR,DB_USER,DB_PASSWD,DB_NAME)){
        msg = "ser error(mysql connection)";
    }
    stringstream ss;
    string tmp;
    string status;
    ss<<m_fileinfo_.file_size;
    ss>>tmp;
    if(m_fileinfo_.trans_status){
        status = "ok";
    }
    else{
        status = "er";
    }

    string insetSQL = "INSERT INTO files valuse("+m_fileinfo_.file_name+","+user_id+","
                       +m_fileinfo_.file_md5+","+m_fileinfo_.file_path+","+tmp+","+status+");";
    
    db->execSQL(insetSQL);

    msg=*(db->getResult()).begin();
    if(strncmp("1",msg.c_str(),1) == 0){
        msg = "file insert to mysql error";
    }
    return true;

}

bool fileTrans::sendFile()
{
    int fd = open((m_fileinfo_.file_path).c_str(),O_RDONLY);
    if (fd<0){
        cout<<"open file false"<<endl;
        return true;
    }
    struct stat statBuf ;
    /* Get file attributes for the file, device, pipe, or socket
    that file descriptor FD is open on and put them in BUF.  */
    fstat(fd,&statBuf);
    sendfile(connfd,fd,NULL,statBuf.st_size);
    return 0;
}

bool fileTrans::removeFile(string path)
{
    MyDB *db= new MyDB();
    if (!db->initDB(SER_ADDR,DB_USER,DB_PASSWD,DB_NAME)){
        msg = "ser error(mysql connection)";
        return false;
    }

    string selectSQL = "select count(*) from files where user_id"+user_id+"and file_path = "+path+";";
    db->execSQL(selectSQL);
    msg = *(db->getResult()).begin();
    if(strncmp("1",msg.c_str(),1)!=0){
        msg = "The user does not have this file";
        return false;
    }

    //delete values from memcached
    selectSQL = "select file_md5 from file where user_id ="+user_id+" and file_path"+path+";";
    db->execSQL(selectSQL);
    
    Mcache mem(SER_ADDR,MemCache_Port);
    mem.deleteKey( ( *(db->getResult()).begin()).c_str() ) ;

    //delete mysql value
    selectSQL = "delete from files where user_id"+user_id +" and file_path "+path+";";
    db->execSQL(selectSQL);

    return true;
}

bool fileTrans::createFile()
{
    int nbytes = -1;
    int fd = open((m_fileinfo_.file_path).c_str(),O_WRONLY|O_CREAT|O_TRUNC,0666);
    if (fd == -1){
        ERR_EXIT("open file error");
        return false;
    }

    char recvBuf[BUFFSIZE] ={0};
    while (nbytes = recv(trans_fd,recvBuf,64,0)>0)
    {
        int writeBytes = write(fd,recvBuf,nbytes);
        if(writeBytes != nbytes){
            ERR_EXIT("write file error");
            return false;
        }
        if(nbytes < 64){
            break;
        }    
    }
    return true;
}

void fileTrans::showFileList()
{
    MyDB *db = new MyDB();
    if(!db->initDB(SER_ADDR,DB_USER,DB_PASSWD,DB_NAME))
    {
        msg = "ser error(mysql connecting)";
        return;
    }
    //查询user_id的所有文件名
    string selectSql="select file_name from files where user_id="+user_id+";";
    db->execSQL(selectSql);
    list<string> res=db->getResult();
    //msg保存查询出来的文件名，以" "分开，传回客户端
    list<string>::iterator it;
    for(it=res.begin();it!=res.end();++it)
    {
        msg += *it;
        msg += " ";
    }
}

int main()
{
    fileTrans ft(Transport_Port,SER_ADDR);
    ft.Run();
    return 0;
}
