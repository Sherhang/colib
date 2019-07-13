#include <iostream>
#include "co_routine.h"
#define ToString(x) #x
using namespace std;

int main()
{
    int n=10;
    string a= ToString(987654);
    cout<<a<<endl;
}
