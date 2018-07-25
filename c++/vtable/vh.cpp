#include <iostream>

using namespace std;

struct GrandParent {
    virtual void f() {}
    long d1 = 1;
};

struct Mother: virtual GrandParent {
    virtual void g() {}
    long d2 = 2;
};

struct Father: virtual GrandParent {
    virtual void h() {}
    long d3 = 3;
};

struct Child: Mother, Father {
    virtual void foo() {}
    long d4 = 4;
};

int main()
{
    GrandParent gp;
    Mother m;
    Father f;

    Child c;

    Child *pc = &c;
    pc->foo();

    Mother *pm = &c;
    pm->g();

    Father *pf = &c;
    pf->h();

    GrandParent *pg = &c;
    pg->f();

    return 0;
}
