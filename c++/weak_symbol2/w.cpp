#include <iostream>

using namespace std;

extern void f() __attribute__((weak));

void f()
{
    cout << __FILE__ << "|" << __func__ << "|" << __LINE__ << endl;
}
