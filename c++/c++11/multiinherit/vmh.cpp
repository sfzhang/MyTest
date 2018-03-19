#include <iostream>

using namespace std;

struct B {
    B(int i): m_i(i) { cout << "B::B() " << m_i << endl; }
    int m_i;
};

struct C1: virtual B {
    C1(int i = 0): B(i) { cout << "C1::C1() " << endl; }
};

struct C2: virtual B {
    C2(int i = 1): B(i) { cout << "C2::C2() " << endl; }
};

struct D: C1, C2 {

    /* error: no matching function for call to ‘B::B()’
    D(): C1(0), C2(1) { cout << "D::D() " << endl; }
    D() { cout << "D::D() " << endl; }
    */

    /**
     * Virtual constructor B::B() must constructor here
     * get result:
     * B::B() 100
     * C1::C1() 
     * C2::C2() 
     * D::D()
     */
    //D(): B(100), C1(0), C2(1) { cout << "D::D() " << endl; }
    D(): B(100) { cout << "D::D() " << endl; }
};

int main()
{
    D d;
    return 0;
}
