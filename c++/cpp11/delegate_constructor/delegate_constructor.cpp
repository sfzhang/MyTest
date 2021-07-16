#include <iostream>

using namespace std;

struct A {

    A(int a, int b): m_a(a), m_b(b) {}

    //error: mem-initializer for ‘A::m_c’ follows constructor delegation
    //A(): A(0, 0), m_c(3) {}

    A(): A(0, 0) {}
    int m_a;
    int m_b;
    int m_c;
};

struct B {

    B(int) { throw 0; }

    B()
        try: B(0) {
            cout << "no throw" << endl;
        }
        catch (...) {
            cout << "catch exception" << endl;
            throw 1.0;
        }
};

int main()
{
    A a;

    try {
        B b;
    }
    catch (...) {
        cout << "main catch" << endl;
    }

    return 0;
}
