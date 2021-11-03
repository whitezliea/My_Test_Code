#ifndef _MYDB_H
#define _MYDB_H
#include<iostream>
#include<string>
#include<stack>
#include<algorithm>
#include</usr/include/mysql/mysql.h>
using namespace std;
class MyDB
{
private:
    MYSQL *mysql_TEST;  // mysql connection handle pointer
    MYSQL_RES *result;
    MYSQL_ROW row;   //Query information returned by line
public:
    MyDB(/* args */);
    ~MyDB();
    bool initDB(string host,string user,string password,string db_name);
    bool execSQL(string sql);
};



#endif