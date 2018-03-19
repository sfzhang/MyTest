#include <iostream>

using namespace std;

struct Ref {
    int &r_i;

    Ref(int &i): r_i(i)
    {
        // error: uninitialized reference member in ‘int&’
        // r_i = i;
    }
};

int main()
{
    int a = 0;

    Ref r(a);

    return 0;
}
