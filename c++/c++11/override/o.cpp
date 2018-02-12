/* override */
#include <iostream>
#include <string>

using namespace std;

class B {

public:

    virtual void vf() = 0;

    virtual void vf(int a) = 0;

    void f2()
    {
        cout << "f2" << endl;
    }

    void f2(int a)
    {
        cout << "f2(): " << a << endl;
    }

};

class C: public B {

public:

    virtual void vf() override
    {
        cout << "v" << endl;
    }

    virtual void vf(int a) override
    {
        cout << "vf: " << a << endl;
    }

    virtual void vf(double a)
    {
        cout << "vf: " << a << endl;
    }
};

class D: public C {

public:

    void vf(string s)
    {
        cout << __func__ << ": " << s << endl;
        C::vf(3.14);
    }
};

int main()
{
    C c;
    c.vf();
    c.vf(3.5);

    D d;
    d.vf("abc");

    return 0;
}
