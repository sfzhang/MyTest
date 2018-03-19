#include <iostream>

using namespace std;

int add(int a, int b)
{
    return a + b;
}

typedef int (*add_t)(int, int);

int main()
{
    add_t a = add;
    void *vp = a;

    cout << a(1, 2) << endl;

    return 0;
}
