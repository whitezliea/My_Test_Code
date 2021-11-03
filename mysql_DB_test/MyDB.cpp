/*
    Reference URL: 
    http://www.manongjc.com/detail/23-cdafymnuvpwnicp.html
    https://www.cxyzjd.com/article/qq_38570571/79870763
*/

#include<iostream>
#include<string>
#include"MyDB.h"

using namespace std;

MyDB::MyDB()
{
   mysql_TEST = mysql_init(NULL);  //mysql connection init.
   if(mysql_TEST==NULL){
       cout<<"Error: "<<mysql_error(mysql_TEST);
    exit(1);
   }

}

MyDB::~MyDB()
{
    if(mysql_TEST != NULL){
        mysql_close(mysql_TEST);
    }
}

bool MyDB::initDB(string host,string user,string password,string db_name)
{
    mysql_TEST = mysql_real_connect(mysql_TEST,host.c_str(),user.c_str(),password.c_str(),db_name.c_str(),0,NULL,0);
    if (mysql_TEST == NULL){
        cout<<"Error: "<<mysql_error(mysql_TEST);
        exit(1);
    }
    return true;
}

bool MyDB::execSQL(string sql)
{
    if (mysql_query(mysql_TEST,sql.c_str())){
        cout<<"Query Error: "<<mysql_error(mysql_TEST);
        return false;
    }
    else{
        result = mysql_store_result(mysql_TEST);
        if(result){
            int num_fileds = mysql_num_fields(result);  // Get the number of columns
            int num_rows = mysql_num_rows(result);  //get the number of rows.
            cout<<"num_fields: "<<num_fileds<<endl;
            cout<<"num_rows: "<<num_rows<<endl;
            for(int i=0;i<num_rows;i++){
                row = mysql_fetch_row(result);
                if(row<0){
                    break;
                }
                for (int j=0;j<num_fileds;j++){
                    if (row[j]==NULL){
                        cout<<"nulls"<<"\t\t";
                    }
                    else{
                        cout<<row[j]<<"\t\t";
                    }
                }
                cout<<endl;
            }
        }
        else{  //result = NULL
            if (mysql_field_count(mysql_TEST)==0) { //exec update,inset,delete etc , Non-query statement
                // it was not a SELECT
                 int num_rows = mysql_affected_rows(mysql_TEST); //Returns the number of rows affected by update, insert, and delete
                 
            }
            else{
                cout<<"Get result error: "<<mysql_error(mysql_TEST);
                return false;
            }
        }
        cout<<endl;cout<<endl;cout<<endl;

    }
    return true;
    
}