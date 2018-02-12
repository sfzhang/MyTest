/* Directly initialize */

#include <iostream>

using namespace std;

class C {

public:

    C(int _a): a(_a), c('c'), d(0) {}

    int a = 1;
    double b = 2.5;
    char c{'a'};
    float d;
};

int main()
{
    C c(100);

    cout << "a: " << c.a << endl;
    cout << "b: " << c.b << endl;
    cout << "c: " << c.c << endl;
    cout << "d: " << c.d << endl;

    return 0;
}
