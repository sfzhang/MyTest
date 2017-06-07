#include <iostream>

using namespace std;

class A {
public:
    virtual void dump()
    {
        cout << a << endl;
    }

    const static int a;
};

const int A::a = 1;

class B: public A {
public:
    virtual void dump()
    {
        cout << a << endl;
    }

    const static int a;
};

const int B::a = 2;

int main()
{
    A *a = new B();
    a->dump();

    a = new A();
    a->dump();

    return 0;
}

