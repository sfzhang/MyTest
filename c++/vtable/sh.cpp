#include <iostream>

using namespace std;

struct Base {
    virtual void f() {}
    virtual void g() {}
};

struct Derived: Base {
    virtual void f() override {}
    virtual void h() {}
};

int main()
{
    Base b1, b2;
    Derived d1, d2;

    return 0;
}

