#include <iostream>

using namespace std;

struct A {

    A(int a = 1, float f = 2, double d = 3):
        m_a(a), m_f(f), m_d(d) {}

    int m_a;
    float m_f;
    double m_d;
};

struct B: public A {

    using A::A;

    void print()
    {
        cout << m_a << "; " << m_f << "; " << m_d <<endl;
    }

};

int main()
{
    B b;
    b.print();

    B b1(2);
    b1.print();

    B b2(100, 0.1);
    b2.print();

    B b3(9, 10.1, 5.5);
    b3.print();

    return 0;
}


