/*co_routine.h基础测试，
**只用到poll， co_eventloop ，co_enable_hook_sys();
**程序实现两个子协程交替运行，但程序是不会退出的
*/

#include <iostream>
#include <unistd.h>
#include <ctime>
#include <sys/select.h>
#include "co_routine.h"
using namespace std;

void* f1(void *arg)
{
	co_enable_hook_sys();
	for(int i=0;i<10;i++)
	{
		cout<<__func__<<" "<<i<<endl;
		poll(NULL,0,100);
	}
	return NULL;
}

void* f2(void *arg)
{
	co_enable_hook_sys();
	for(int i=0;i<10;i++)
	{
		cout<<__func__<<" "<<i<<endl;
		poll(NULL,0,100);
	}
	return NULL;
}

int main()
{
    stCoCond_t* cond=co_cond_alloc();
	
    stCoRoutine_t* f1_routine;
    co_create(&f1_routine,NULL,f1,cond);
    co_resume(f1_routine);
	
    stCoRoutine_t* f2_routine;
    co_create(&f2_routine,NULL,f2,cond);
    co_resume(f2_routine);
    cout<<__func__<<endl;   
    co_eventloop(co_get_epoll_ct(),NULL,NULL);
	cout<<__func__<<" after "<<endl;
    return 0;
}
