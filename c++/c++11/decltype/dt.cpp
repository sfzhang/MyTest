/* decltype */
#include <iostream>
#include <typeinfo>
#include <type_traits>

using namespace std;

struct C {

    int foo(int i) { return i; }

    auto g(int x) -> result_of<decltype(&C::foo)(C, int)>::type
    {
        return x;
    }

    void g() {};

    static void f() {};

    /* overload error for decltype */
    //static void f(int) {};
};

int main()
{
    int i;
    decltype(i) j;
    cout << typeid(j).name() << endl;

    float a;
    double b;
    decltype(a + b) c;
    cout << typeid(c).name() << endl;

    decltype(C::f) f;

    decltype(((C *)0)->foo(3)) foo;

    cout << typeid(foo).name() << endl;

    decltype(&C::foo) f2;
    cout << typeid(f2).name() << endl;

    decltype(&C::f) f3;
    cout << typeid(f3).name() << endl;

    return 0;
}
