#include <iostream>
using namespace std;

int a[10];

int main()
{
//    void *p[64] = { nullptr };
    void *p[64];

    for (int i = 0; i < 64; i++) {
        if (p[i]) {
            cout << "not null: " << i << endl;
        }
    }

    cout << &a[9] - &a[5] << endl;
    void *msg;
    cout << (int*)(msg + sizeof(int)) << endl;

    cout << (long)msg << endl;
    cout << (long)(msg + sizeof(int)) << endl;
    return 0;
}
