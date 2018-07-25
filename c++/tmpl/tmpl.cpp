#include <iostream>

using namespace std;

template <typename T>
int f(T a)
{
    return g(a);
}

struct C {};

int g(C c)
{
    return 0;
}

int g(int i)
{
    return i;
}

int main()
{
    // Works!
    //int z = f(C{});

    // Error: no declarations were found by argument-dependent lookup at the point of instantiation
    int z = f(10);

    cout << z << endl;
    return 0;
}
