#include <iostream>

using namespace std;

struct B {

    virtual void f() {}
    virtual void g() = 0;
};

struct C1: virtual public B {
    void f() override
    {
    }
};

struct C2: virtual public B {
    void f() override
    {
    }
};

struct D: C1, C2 {
    /**
     * error: no unique final overrider for ‘virtual void B::f()’ in ‘D’ if not define f() here
     * C++11 Standard 10.3/2 "In a derived class, if a virtual member function of a base classu
     * subobject has more than one final overrider the program is ill-formed." 
     */
    void f() override
    {
        B::f();
    }

    void g() final
    {
    }
};

int main()
{
    D d;
    return 0;
}
