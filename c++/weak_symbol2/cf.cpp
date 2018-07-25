#include <iostream>
using namespace std;

extern void f();

void call_f()
{
    cout << "call raw_f: " << endl;
    f();
}

