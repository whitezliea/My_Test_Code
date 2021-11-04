#include <iostream>
#include "public.h"
using namespace  std;
void Server_DIR();
int main() {
    string s;
    std::cout << "Hello, World!" << std::endl;
    Server_DIR();

    return 0;
}

//exit: 1 ; not exit: 0
int IsFileExit(const char *path)
{
    return !access(path,F_OK); //access success : 0 ,fault 1;
}

void Server_DIR()
{
    char *home;
    home = getenv("HOME");  //get environment variable ; //=echo $HOME
    //printf("the home path is %s\n", home);

    string defaultPath = home;
    string server_path = defaultPath + "/CloudPan/clidir/";
    cout<<"path : "<<server_path<<endl;
    const char *path = server_path.c_str();
    if (IsFileExit(path)==0) {
        string cmd;
        cmd = " mkdir -p " + server_path;
        cout<<"mkdir success"<<endl;
        system(cmd.c_str());
    }
    else
    {
        cout<<"file already exit";
    }


}

