#include <iostream>
#include <typeinfo>

using namespace std;

template <typename T>
void f(T a)
{
    cout << typeid(a).name() << endl;
}

int main()
{
    const char *a = "abc";
    f(a);

    const char &b = *a;
    f(b);

    char c[13];
    f(c);

    const char d[1] = {'a'};
    f(d);


    auto t = {1};
    cout << typeid(t).name() << endl;

    auto l{2};
    cout << typeid(l).name() << endl;

    return 0;
}
