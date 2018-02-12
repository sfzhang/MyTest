/* Deride constructor */

#include <iostream>

using namespace std;

struct A {

    A(int a): m_a(a) {}

    int m_a;
};

struct B {

    B(int b): m_b(b) {}

    int m_b;
};

struct C: public A, B {

    using A::A;
    using B::B;

    C(int c): A(c), B(c) {}

};

int main()
{
    C c(1);

    return 0;
}
