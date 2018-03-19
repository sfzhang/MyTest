#include <iostream>

using namespace std;

struct B {
    B(int i): m_i(i) { cout << "B::B() " << m_i << endl; }
    int m_i;
};

struct C1: B {
    C1(int i): B(i) { cout << "C1::C1() " << endl; }
};

struct C2: B {
    C2(int i): B(i) { cout << "C2::C2() " << endl; }
};

struct D: virtual C1, virtual C2 {

    /**
     * Not virtual inherit, B::B() call twice
     * B::B() 0
     * C1::C1() 
     * B::B() 1
     * C2::C2() 
     * D::D()
     */
    D(): C1(0), C2(1) { cout << "D::D() " << endl; }

    /**
     * error: type ‘B’ is not a direct or virtual base of ‘D’
    D(): B(100), C1(0), C2(1) { cout << "D::D() " << endl; }
     */
};

int main()
{
    D d;
    return 0;
}
