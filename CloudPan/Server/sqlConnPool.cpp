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
    
}