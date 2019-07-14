#include <iostream>
#include <unistd.h>
#include <ctime>
#include <sys/select.h>
#include "co_routine.h"
using namespace std;
void* f1(void *arg)

{
    stCoCond_t* cond=(stCoCond_t*)arg;
    for(int s=0;s<5;s++)
    {
    cout<<__func__<<endl;

    co_enable_hook_sys();

    for(uint64_t i =0;i<10000;i++)
        for(uint64_t j=0;j<10000;j++)
            int k=i*j+j-i;
    cout<<__func__<<" for end "<<endl;
    
    timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = 20 * 1000; // 20 ms
    select(0, NULL, NULL, NULL, &delay);
    co_cond_signal(cond);
    poll(NULL,0,1);

    }
    co_yield_ct();
    return NULL;
}
void* f2(void * arg)
{
    stCoCond_t* cond=(stCoCond_t*)arg;
    for(int s=0;s<5;s++)
    {
    cout<<__func__<<endl;

    co_enable_hook_sys();

    for(uint64_t i =0;i<10000;i++)
        for(uint64_t j=0;j<10000;j++)
            int k=i*j+j-i;
    cout<<__func__<<" for end "<<endl;
    
    timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = 20 * 1000; // 20 ms
    select(0, NULL, NULL, NULL, &delay);
    cout<<__func__<<" delay end"<<endl;
    co_cond_signal(cond); 
    poll(NULL,0,100);

    }
    co_yield_ct();
    return NULL;
}

int main()
{
    stCoCond_t* cond=co_cond_alloc();
    double start_time=clock();
    stCoRoutine_t* f1_routine;
    co_create(&f1_routine,NULL,f1,cond);
    co_resume(f1_routine);
    stCoRoutine_t* f2_routine;
    co_create(&f2_routine,NULL,f2,cond);
    co_resume(f2_routine);
	
    cout<<__func__<<endl;
    
    co_eventloop(co_get_epoll_ct(),NULL,NULL);
    double end_time=clock();
    double all_time=(end_time-start_time)/1000.0;
    cout<<"执行时间："<<all_time<<"ms"<<endl;
    return 0;
}
