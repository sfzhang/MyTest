#include <iostream>

using namespace std;

namespace n {
    struct C {};
    void f(C)
    {
        cout << "c" << endl;
    }
}

void f(int)
{
    cout << "int" << endl;
}

template <typename T>
void g(T t)
{
    f(t);
}

void f(double)
{
    cout << "double" << endl;
}

int main()
{
    g(n::C{}); // n::f(C)
    g(2);      // f(int)
    g(2.2f);   // f(int)

    return 0;
}
