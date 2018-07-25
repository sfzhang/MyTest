#include <iostream>

using namespace std;

//extern void print() __attribute__((weak));
void print()
{
    cout << __FILE__ << "|" << __func__ << "|" << __LINE__ << endl;
}

