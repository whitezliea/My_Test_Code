#include<iostream>
#include"MyDB.h"
using namespace std;

int main()
{
    MyDB db;
    db.initDB("localhost","root","root","test");
    //db.execSQL("SELECT * FROM test_tbl_2");
    db.execSQL("SELECT * FROM test_tbl_2");
    
    db.execSQL("INSERT INTO test_tbl_2 \
      (test_title, test_author, submission_date) \
      VALUES \
      (\"learn MySQL\", \"hello world\", '2020-04-28');  ");
    db.execSQL("SELECT * FROM test_tbl_2");
    return 0;
}
