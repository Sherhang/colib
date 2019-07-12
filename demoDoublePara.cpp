#include <iostream>
#include "co_routine.h"

using namespace std;
struct IN_OUT{
	string *person;
	string* name;
};

int getName(const string&  person,string& name)
{
	cout<<"running "<<__func__<<endl;
	name=person;
	return 1;
}

void * co_getName(void* arg)
{
	cout<<"running "<<__func__<<endl;
	IN_OUT* in_out=(IN_OUT*)arg;
	int ret = getName(*(in_out->person),*(in_out->name));
	return NULL;
}

int main()
{
	string person="Tom";
	string name="unknown";
	IN_OUT* arg=new IN_OUT;
	arg->name=&name;
	arg->person =&person;
	
	stCoRoutine_t* getName_routine;
	cout<<"running "<<__func__<<endl;
	co_create(&getName_routine,NULL,co_getName,arg);
	co_resume(getName_routine);
	cout<<"name is "<<*(arg->name)<<endl;
}
