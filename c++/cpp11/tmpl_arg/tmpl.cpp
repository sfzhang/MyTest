#include <iostream>

using namespace std;

template <typename T1 = int, typename T2 = bool>
class C {};

template <typename T1 = int, typename T2>
void f(T1 a, T2 b)
{
}

int main()
{
    return 0;
}

