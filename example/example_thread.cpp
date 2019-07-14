/*
* Tencent is pleased to support the open source community by making Libco available.

* Copyright (C) 2014 THL A29 Limited, a Tencent company. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License"); 
* you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, 
* software distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and 
* limitations under the License.
*/



#include "co_routine.h"
#include "co_routine_inner.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int loop(void *)
{
    sleep(1);
    cout<<__func__<<endl;	
    return 0;
}
static void *routine_func( void * )
{
    cout<<__func__<<" start"<<endl;	
    stCoEpoll_t * ev = co_get_epoll_ct(); //ct = current thread
    for(int i=0;i<5;i++)   
        cout<<"for "<<i<<endl;
    co_eventloop( ev,loop,0 );
    cout<<__func__<<" end"<<endl;
	return NULL ;
}
int main(int argc,char *argv[])
{
    cout<<__func__<<" start"<<endl;
	int cnt = atoi( argv[1] );

	pthread_t tid[ cnt ];
	for(int i=0;i<cnt;i++)
	{
		pthread_create( tid + i,NULL,routine_func,0);
	}

    cout<<__func__<<" end"<<endl;
    pthread_exit(NULL);
	return 0;
}

