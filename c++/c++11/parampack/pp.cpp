#include <iostream>

using namespace std;

template <typename T>
T power(T t)
{
    return t * t;
}

template <typename T>
auto sum(T t) -> decltype(t)
{
    return t;
}

template <typename T, typename... Rest>
T sum(T t, Rest... rest)
{
    return t + sum(power(rest)...);
}

int main()
{
    cout << sum(1, 2.0l, 3) << endl;
    /*
     * 1 + sum(power(2.0l), power(3))
     * 1 + power(2.0l) + sum(power(power(3)))
     * 1 + 4 + 81
     */

    return 0;
}

