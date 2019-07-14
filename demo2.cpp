#include "co_routine.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <stack>
 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
 
#include <sys/epoll.h>
#ifdef __FreeBSD__
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#endif
 
#include<iostream>
using namespace std;
 
struct task_t
{
    stCoRoutine_t *co;
    int epFd;
};
typedef struct task_t task_t;
 
int myErrorOperate(char const * const error_str,int error_line,int error_exit=1)
{
    perror(error_str);
    printf("%d\n",error_line);
    if(error_exit==1)
        exit(1);
    return 0;
}
int co_accept(int fd, struct sockaddr *addr, socklen_t *len );
static void* mcoListen(void *arg_co)
{
   // task_t &co=*(task_t*)arg_co;
    co_enable_hook_sys();
    int lsEpFd;
    lsEpFd=epoll_create(100);
    if(lsEpFd<0)
    {
        myErrorOperate("create listen_epfd err",__LINE__);//exit
    }
    int lsSocketFd;
    if((lsSocketFd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
   //     free(lsEpFd);
        myErrorOperate("create listen_socket fd err.",__LINE__);//exit
    }
    //set socket opt
    int ret,val=1;
    ret=setsockopt(lsSocketFd,SOL_SOCKET,SO_REUSEADDR,(void*)&val,sizeof(val));
        //reuse addr
    if(ret<0)
    {
        myErrorOperate("set SO_REUSEADDR err.",__LINE__,0);
    }
 
    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(sockaddr_in));
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=INADDR_ANY;
    saddr.sin_port=htons(8001);
    ret=bind(lsSocketFd,(struct sockaddr*)&saddr,sizeof(struct sockaddr_in));
    if(ret<0)
    {
        myErrorOperate("lsten socket bind err.",__LINE__,1);//exit
    }
    ret=listen(lsSocketFd,1024);//backlog
    if(ret<0)
    {
        myErrorOperate("listen err.",__LINE__,1);//exit
    }
 
    cout<<"Accepting connections..."<<endl;
    socklen_t saddrLen;
    for(;;)
    {
        saddrLen=sizeof(saddr);
        ret=co_accept(lsSocketFd,(struct sockaddr*)&saddr,&saddrLen);
       if(ret<0)//每次poll超时后都需要重新加入。
        {
            struct pollfd pf={0};
            pf.fd=ret;              //关心epoll事件
            pf.events=(POLLIN|POLLERR|POLLHUP);
            co_poll(co_get_epoll_ct(),&pf,1,1000);//yield   同时关心epoll事件，和1000ms的超时事件
        }
        if(ret>0)
        {
            cout<<ret<<endl;
        }
    }
}
void * print(void *args)
{
    co_enable_hook_sys();
    for(;;)
    {
        cout<<"time 0.5"<<endl;
        struct pollfd pf={0};//不关心epoll时间，只关心时间轮超时事件。
        co_poll(co_get_epoll_ct(),&pf,1,500);//500ms打印一次
    }
}
int main() {
    task_t coLs;
    stCoRoutine_t *time;
    co_create(&time,NULL,print,NULL);
    co_resume(time);//启动0.5s计时打印函数
 
    co_create(&(coLs.co),NULL,mcoListen,&coLs);
    co_resume(coLs.co);//启动接受连接函数，接受任何连接请求，打印sokecfd，然后不做任何事情
    cout<<"listen co init complete."<<endl;
    co_eventloop(co_get_epoll_ct(),0,0);
}