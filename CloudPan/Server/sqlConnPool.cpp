#include<sqlConnPool.h>
#include<stdexcept>
#include<cppconn/config.h>
#include<cppconn/connection.h>

using namespace std;
using namespace sql;

CSqlConnPool::CSqlConnPool()
{
    driver_ = NULL;
    DBName_ = NULL;
}

CSqlConnPool::~CSqlConnPool()
{
    Destroy();
}


void CSqlConnPool::Init(const SqlConnInfo & sqlConnInfo)
{
    sqlConnInfo_ = sqlConnInfo;
    
    try
    {
        this->driver_= get_driver_instance();
    }
    catch(const std::exception& e)
    {
        //std::cerr << e.what() << '\n';
        cout<<"CSqlConnPool::Init:SQLException" << e.what()<<endl;
    }
    catch (std::runtime_error &e)
    {
        cout<< "CSqlConnPool::Init:runtime_error" << e.what()<<endl;
    }
    
    for(int i = 0;i<sqlConnInfo_.max_conn_num;++i)
    {
        Connection *conn  = this->CreateConnection();
        if (conn){
            queue_conn_.push_back(conn);
        }
        else{
            cout<<"CSqlConnPool::Init:connection failed! index = "<<i<<endl;
        }
    }
    cout<<"Create "<<queue_conn_.size()<< " new connection!"<<endl;
}

void CSqlConnPool::SetDBName(const char *DBName)
{
    DBName_ = DBName;
}

void CSqlConnPool::Destroy()
{
    for(deque<sql::Connection*>::iterator pos = queue_conn_.begin(); pos != queue_conn_.end();++pos){
        this->TerminateConnection(*pos);
    }
    queue_conn_.clear();
}

sql::Connection * CSqlConnPool::CreateConnection()
{
    sql::Connection *conn = NULL;
    try
    {
        std::string url = string("tcp://")+ sqlConnInfo_.ip + string(":") + sqlConnInfo_.port;
    }
    catch(const std::exception& e)
    {
        cout<< "CSqlConnPool::CreateConnection:SQLException=" << e.what()<<endl;
    }
    catch (std::runtime_error &e)
    {
        cout<<"CSqlConnPool::CreateConnection:runtime_error=" << e.what()<<endl;
    }
    
    return conn;
}

void CSqlConnPool::releaseConnection_(sql::Connection *conn)
{
    if(conn){
        boost::unique_lock<boost::mutex> lock(mutex_);
        bool found = false;
        for(deque<sql::Connection*>::iterator pos = queue_conn_.begin();pos!=queue_conn_.end();++pos){
            if (*pos == conn){
                found = true;
                break;
            }
            if (!found){
                queue_conn_.push_back(conn);
            }
        }
    }
}

void CSqlConnPool::TerminateConnection(sql::Connection * conn)
{
    if(conn){
        try
        {
            conn->close();
        }
        catch(const std::exception& e)
        {
            cout<<"CSqlConnPool::TerminateConnection failed: unknown reason."<<endl;
        }

        delete conn;
        conn = NULL;
        
    }
}


bool CSqlConnPool::IsValidConnection(sql::Connection *conn)
{
    bool ret = true;
    try
    {
        conn->setSchema(DBName_);
    }
    catch(...)
    {
        ret = false;
    }
    return ret;
}


sql::Connection * CSqlConnPool::GetConnection()
{
    sql::Connection * conn =NULL;
    boost::unique_lock<boost::mutex> lock(mutex_);

    if(!queue_conn_.empty()){
        conn = queue_conn_.front();
        queue_conn_.pop_front();
    }

    //If the connection is not a null pointer, first determine whether it has expired
    if(conn){
        if(!this->IsValidConnection(conn)){
            this->TerminateConnection(conn);
        }
    }
    
    if(conn==NULL){
        conn = this->CreateConnection();
        if(conn!=NULL)
        {
            conn->setSchema(DBName_);
    }
    return conn;
}

/*
int main()
{
    const SqlConnInfo conInfo={10,"127.0.0.1","3306","root","qinyu"};

    CSqlConnPool pool;
    pool.Init(conInfo);
    pool.SetDBName("FTP");

    Connection *conn;
    Statement *state;
    ResultSet *result;
    //MYSQL *result;

    conn=pool.GetConnection();
    state = conn->createStatement();
    state->execute("use FTP");
    result = state->executeQuery("select *from user");
    size_t i = result->rowsCount();
    cout<<i<<endl;
    cout<<"password "<<result->findColumn("password")<<endl;
    while(result->next())
    {
        //cout<<result->getCursorName()<<" ";
        string name=result->getString("user_id");
        string password=result->getString("password");
        int i=result->getInt("friends_id");
        int j=result->getInt("file_id");
        cout<<result->getRow()<<":"<<name<<" "<<password<<" "<<i<<" "<<j<<endl;
    }

    //conn->setAutoCommit(0);
    //cout<<"DataBae model:"<<conn->getAutoCommit()<<endl;
    //cout<<"main :: conn "<<conn<<endl;
 
    delete conn;

    return 0;
}*/