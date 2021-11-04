//
// Created by white on 11/1/21.
//

#ifndef CLOUDPAN_MYDB_H
#define CLOUDPAN_MYDB_H

#include "../public.h"
#include "/usr/include/mysql/mysql.h"

class MyDB {
public:
    MyDB();
    ~MyDB();
    bool initDB(string host,string user,string password, string db_name);
    bool execSQL(string sql);
    void showResult();
    list<string> getResult();

private:
    MYSQL *Mysql_Connection;
    MYSQL_RES *Mysql_Result;
    MYSQL_ROW Mysql_Row;
    list<string> res;
};


#endif //CLOUDPAN_MYDB_H
