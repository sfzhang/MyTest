#include <iostream>

using namespace std;

struct Mother {
    virtual void f() {}
    virtual void g() {}
    int d1 = 1;
};

struct Father {
    virtual void h() {}
    virtual void m() {}
    int d2 = 2;
};

struct Child: Mother, Father {
    virtual void f() override {}
    virtual void m() override {}
    virtual void n() {}
    int d3 = 3;
};

int main()
{
    Child c;

    Child *pc = &c;
    pc->h();
    pc->m();

    Father *pf = &c;
    pf->m();

    return 0;
}
