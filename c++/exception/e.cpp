#include <iostream>

using namespace std;

int f()
{
    throw 1;
}

int g()
{
    try {
        f();
    }
    catch (int a) {
        cout << "a: " << a << endl;
        a = 1;
        throw;
    }
}

int main()
{
    try {
        g();
    }
    catch (int a) {
        cout << "out a: " << a << endl;
    }

    return 0;
}
