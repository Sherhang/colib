#include <iostream>
#include "co_routine.h"
using namespace std;
void * f1(void* s)
{
	string * ss=(string*) s;
	for (size_t i =0;i<5;++i)
	{
		cout<<*ss<<" "<<i<<endl;
	}
	co_yield_ct();
	for(int i=5;i<10;i++)
		cout<<*ss<<" "<<i<<endl;
   
	return NULL;
}

void * f2(void* a)
{
	int *aa=(int*) a;
	for(int i=0;i<5;i++)
			cout<<*aa+i<<endl;
	co_yield_ct();
	for(int i=5;i<10;i++)
			cout<<*aa+i<<endl;
	return NULL;
}

int main()
{
	stCoRoutine_t * cof1;
	stCoRoutine_t* cof2;
	string s="ye";
	string* s_ptr=&s;
	int a=100;
	int * a_ptr=&a;
	co_create(&cof1,NULL,f1,s_ptr);
	co_create(&cof2,NULL,f2,a_ptr);
	co_resume(cof1);
	co_resume(cof2);
	co_resume(cof1);
	co_resume(cof2);
	return 0;
}
