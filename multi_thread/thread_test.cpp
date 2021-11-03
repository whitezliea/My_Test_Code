/*
   Reference URL: 
   https://www.cnblogs.com/skynet/archive/2010/10/30/1865267.html

   Requirments:
   1） 有一int型全局变量g_Flag初始值为0；

   2） 在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1

   3） 在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2

   4） 线程序1需要在线程2退出后才能退出

   5） 主线程在检测到g_Flag从1变为2，或者从2变为1的时候退出
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<cstring>
#include<unistd.h>

typedef void* (*fun)(void*);

int g_Flag = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *_thread_1(void*);
void *_thread_2(void*);

//int pthread_mutex_lock(pthread_mutex_t * mptr);
//int pthread_mutex_unlock(pthread_mutex_t * mptr);
//Both return: 0 if OK, positive Exxx value on error



/*
 * When program is started , a single thread is created, called the initial thread or main thread.
 * Additioanl threads are created by pthread_create.
 * So we just need create two threads in main(). 
 */

int main(int argc,char **argv)
{
    printf("enter main()\n");
    pthread_t _t_id1, _t_id2;
    int rc1 = 0 ,rc2 = 0;
    rc2 = pthread_create(&_t_id2,NULL,_thread_2,NULL);
    if ( rc2 != 0){
        printf("%s: %s\n",__func__,strerror(rc2));
    }
    rc1 = pthread_create(&_t_id1,NULL,_thread_1,NULL);
    if ( rc1 != 0){
        printf("%s: %s\n",__func__,strerror(rc1));
    }

    pthread_cond_wait(&cond,&mutex);
    printf("leave main\n");
    exit(0);
}

/*
 * _thread_1() will be execute by thread1, after pthread_crete()
 * it will set g_Flag = 1;
*/
void* _thread_1(void *arg)
{
    printf("enter thread1\n");
	printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    pthread_mutex_lock(&mutex);
    if (g_Flag == 2){
        pthread_cond_signal(&cond);
    }
	g_Flag = 1;
	printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    pthread_mutex_unlock(&mutex);
    pthread_join(*(pthread_t*)arg,NULL);
	printf("leave thread1\n");
	pthread_exit(0);
}

/*
 * thread2() will be execute by thread2, after pthread_create()
 * it will set g_Flag = 2;
 */
void* _thread_2(void* arg)
{
	printf("enter thread2\n");
	printf("this is thread2, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    pthread_mutex_lock(&mutex);
    if(g_Flag == 1){
        pthread_cond_signal(&cond);
    }
	g_Flag = 2;
	printf("this is thread1, g_Flag: %d, thread id is %u\n",g_Flag, (unsigned int)pthread_self());
    pthread_mutex_unlock(&mutex);
	printf("leave thread2\n");
	pthread_exit(0);
}