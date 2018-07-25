#include <iostream>

using namespace std;

extern void call_weak();

/*
void print()
{
    cout << __FILE__ << "|" << __func__ << "|" << __LINE__ << endl;
}
*/

int main()
{
    call_weak();
}
