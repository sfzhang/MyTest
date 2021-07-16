#include <iostream>

using namespace std;

struct S {

    int m_i;

    S(int i): m_i(i) {}

    ~S() { cout << "S::~: " << m_i << endl; }
};

void e1()
{
    cout << "e1" << endl;
}

void e2()
{
    cout << "e2" << endl;
}

S g_s{0};

int main()
{
    static S s1{1};

    atexit(e1);
    atexit(e2);

    S s2{2};

    // exit(0);
    return 0;
}
