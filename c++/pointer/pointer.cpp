#include <iostream>
using namespace std;

int a[10];

int main()
{
    cout << &a[9] - &a[5] << endl;
    return 0;
}
