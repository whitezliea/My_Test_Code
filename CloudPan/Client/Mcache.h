#ifndef CLOUDPAN_MCACHE_H
#define CLOUDPAN_MCACHE_H

#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<libmemcached/memcached.h>
using namespace std;

class Mcache
{
public:
    Mcache(const char *ip, int port)
    {
        memc = memcached_create(NULL);
        servers = memcached_server_list_append(NULL,ip,port,&rc);
        rc = memcached_server_push(memc,servers);
        memcached_server_free(servers);
    }

    ~Mcache()
    {
        memcached_free(memc);
    }

    bool insertValue(const char*key ,const char *value,int timeout)
    {
        rc = memcached_set(memc,key,strlen(key),value,strlen(value),(time_t)timeout,(uint32_t)0);
        if (rc == MEMCACHED_SUCCESS){
            cout<<"Save key: "<<key<<"  data: "<<value<<endl;
        }
        else{
            return false;
        }
        return true;
    }

    char *getValue(const char *key)
    {
        if(NULL==key){
            cout<<"Key is empty"<<endl;
            return NULL;
        }
        time_t expiration = 3;
        size_t value_length;
        uint32_t flags;
        char *value =NULL;

        value = memcached_get(memc,key,strlen(key),&value_length,&flags,&rc);
        if(rc == MEMCACHED_SUCCESS){
            cout<<"Get Key: "<<key<<" data: "<<value<<endl;
            return value;
        }
        return NULL;
    }

    bool deleteKey(const char *key)
    {
        rc = memcached_delete(memc,key,strlen(key),time_t(0));
        if (rc == MEMCACHED_SUCCESS){
            cout<<"Delete key :"<<key<<endl;
            return true;
        }
        return false;
    }
    
private:
    memcached_st *memc;
    memcached_return   rc;
    memcached_server_st *servers;
};




#endif

