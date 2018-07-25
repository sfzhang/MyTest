#include <iostream>
#include <cstring>
using namespace std;

int a[10];

struct C {
    void f() {}
    virtual void g() {}
};

int main()
{
    //void *p[64] = { nullptr };
    /*
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
    */

    int a[2][8];
    printf("a: %p\n", a);
    for (int i = 0; i < 2; i++) {
        printf("a[%i]: %p\n", i, a[i]);
    }

    int *p1 = &(a[0][0]);
    printf("p1: %p\n", p1);
    int **p = &p1;
    for (int i = 0; i < 2; i++) {
        printf("p[%i]: %p\n", i, p[i * 2]);
    }

    /*
    printf("------------\n");
    int *p2[] = { a[0], a[1] };
    p = p2;
    for (int i = 0; i < 2; i++) {
        printf("p[%i]: %p\n", i, p[i]);
    }
    */

    printf("not virtual: %p\n", &C::f);
    printf("virtual: %p\n", &C::g);
    return 0;
}
