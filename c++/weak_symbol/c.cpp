#include <iostream>

using namespace std;

void print();

void call_weak()
{
    cout << __FILE__ << "|" << __func__ << "|" << __LINE__ << endl;

    print();
}

