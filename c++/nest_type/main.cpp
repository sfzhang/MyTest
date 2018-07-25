#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

typedef string type;

struct C {
    typedef int type;
    C(type t): m_t(t) {}

    // typedef int type;
    // ERROR if defined here!
    int m_t;
    int m_a;
    int m_b;
};

struct B1 {int v1;};
struct B2 {int v2;};
struct D: B1, B2 {int v3;};

int main()
{
    C c(100);

    cout << &c << endl;
    cout << &c.m_t << endl;

    cout << offsetof(C, m_t) << endl;

    int C::*p1 = 0;
    int C::*p2 = &C::m_t;
    int C::*p3 = &C::m_a;
    int C::*p4 = &C::m_b;

    if (p1 == p2) {
        cout << "equal" << endl;
    }

    /* conversion to bool!!!
    cout << &C::m_t << endl;
    cout << &C::m_a << endl;
    cout << &C::m_b << endl; */

    printf("%p\n", p1);
    printf("%p\n", &C::m_t);
    printf("%p\n", &C::m_a);
    printf("%p\n", &C::m_b);

    cout << "-------------------" << endl;
    printf("B1::v1: %p\n", &B1::v1);
    printf("B2::v2: %p\n", &B2::v2);
    printf("D::v1: %p\n", &D::v1);
    printf("D::v2: %p\n", &D::v2);
    printf("D::v3: %p\n", &D::v3);
    return 0;
}
