#include <iostream>

using namespace std;

#define CALL_FUNC(func, str, ...) \
    if (func(__VA_ARGS__) != 0) { \
        cout << #func << ": ne 0" << endl;      \
    } \
    else { \
        cout << #func << ": eq 0" << endl;      \
    }

int fun0()
{
    return 0;
}

int fun1(int a)
{
    return a;
}

int fun2(int a, int b)
{
    return (a + b);
}

int main()
{
    CALL_FUNC(fun0, "fun0:0");
    CALL_FUNC(fun1, "fun1:0", 0);
    CALL_FUNC(fun1, "fun1:1", 1);
    CALL_FUNC(fun2, "fun2:0", 1, -1);
    CALL_FUNC(fun2, "fun2:1", 1, 2);
}
