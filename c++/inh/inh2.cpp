#include <iostream>

using namespace std;

struct B {

    void print()
    {
        cout << "B::print()" << endl;
    }

};

struct C: B {

    void f()
    {
        print();
        cout << "C::f()" << endl;
    }
};

struct D: C {

    void print()
    {
        cout << "D::print()" << endl;
    }

};

int main()
{
    D d;
    d.f();

    return 0;
}
