//
// Created by white on 11/1/21.
// Reference URL:
         //https://www.daimajiaoliu.com/daima/46f97bd07100408
//

#include "MyDB.h"
#include "iostream"
using namespace std;
MyDB::MyDB() {
    Mysql_Connection = mysql_init(NULL);
    if(Mysql_Connection == NULL){
        cout<<"Error"<<mysql_error(Mysql_Connection)<<endl;
        exit(1);

    }
}

MyDB::~MyDB()
{
    if (Mysql_Connection != NULL ){
        mysql_close(Mysql_Connection);
    }
}

bool MyDB::initDB(string host,string user, string password,string db_name)
{
    Mysql_Connection = mysql_real_connect(Mysql_Connection,host.c_str(),user.c_str(),
                                            password.c_str(),db_name.c_str(),0,NULL,0);
    if ( Mysql_Connection == NULL){
        cout<<"Mysql Connection ERROR"<<mysql_error(Mysql_Connection);
        return false;
    }
    return true;
    
}

bool MyDB::execSQL(string sql)
{
    int i,j;
    if (mysql_query(Mysql_Connection,sql.c_str())){
        cout<<"Query Error"<<mysql_error(Mysql_Connection)<<endl;
        exit(1);
    }
    else {
        Mysql_Result = mysql_use_result(Mysql_Connection);

        for(i=0;i<mysql_field_count(Mysql_Connection);++i){  //get Number of columns last time
            Mysql_Row = mysql_fetch_row(Mysql_Result); // get next row from result
            if(Mysql_Row<=0){
                break;
            }
            for(j=0;j<mysql_num_fields(Mysql_Result);++j){   //get Number of columns
                cout<<Mysql_Row[j]<<" ";
                res.push_back(Mysql_Row[j]);
                cout<<"mysql result has been push back!"<<endl;
            }
           
            cout<<endl;
        }
        
        mysql_free_result(Mysql_Result);
    }
    return true;

}

list<string> MyDB::getResult()
{
    return res;
}

void MyDB::showResult()
{
    cout<<"showResult():";
    cout<<res.size()<<endl;
    list<string>::iterator it;
    for (it=res.begin();it!=res.end();it++){
        cout<<*it<<endl;
    }
    cout<<endl;
}

int main1()
{
    MyDB db;
    db.initDB(SER_ADDR,DB_USER,DB_PASSWD,DB_NAME);
    db.execSQL("select * from pan_user");
    db.showResult();
}

