/* explicit */
#include <iostream>

using namespace std;

class E {

public:

    explicit E(int a): m_a(a) {}

    explicit operator bool() const
    {
        cout << "E::operator bool() const" << endl;
        return m_a;
    }

    int m_a;
};

bool check(const E &e)
{
    // return e; // build failed
    return static_cast<bool>(e);
}

class F {

public:

    F(int a): m_a(a) {}

    operator bool() const
    {
        cout << "F::operator bool() const" << endl;
        return m_a;
    }

    int m_a;
};

void print(const F &f)
{
    cout << "F:" << f.m_a << endl;
}

int main()
{
    E e(1);
    if (check(e)) {
        cout << "E is true" << endl;
    }

    F f(0);
    if (!f) {
        print(3);
    }

    return 0;
}
