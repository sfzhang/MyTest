#include <iostream>

using namespace std;

struct A {

    ~A() { throw 1; }
};

void funA()
{
    A a;
}

int main()
{
    funA();

    return 0;
}

