#include <iostream>

using namespace std;

int g_i = 100;

struct S {

    int * p;

    static int s_i;

    void set(int a) const
    {
        *p = a;
    }

    void func()
    {
        constexpr int a = 0;
        auto l = [=]() {
            return s_i + a + g_i + *p;
        };

        //cout << l() << endl;
    }

};

int S::s_i = 1;

void f()
{
    int a = 1;
    int b = 2;

    if (a) {
        static int s = 1;
        auto l = [=]() { return b + s + g_i; };

        auto c = l();

        cout << c << endl;
    }
}

int main()
{
    f();

    int a = 0;
    S s;
    s.p = &a;
    s.set(1);

    int b = 1;
    int c = 1;

    auto l1 = [b]() { return b; };
    auto l2 = [&c]() { return c; };

    b = 2;
    c = 2;

    cout << l1() << endl;
    cout << l2() << endl;

    auto l3 = [=] { return b + c; };
    cout << l3() << endl;

    auto l4 = [=]() mutable { b = 2; };
    auto l5 = [&] { b = 2; };

    return 0;
}
