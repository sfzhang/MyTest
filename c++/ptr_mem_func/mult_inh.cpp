#include <iostream>

using namespace std;

struct A {
    int i;
};

struct B {
    char i;
};

struct C: A, B { };

int main()
{
    C c;
    cout << c.i << endl;

    return 0;
}
