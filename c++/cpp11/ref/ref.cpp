#include <iostream>

using namespace std;

class C
{
    public:
        C() { cout << __func__ << endl; }
        ~C() { cout << __func__ << endl; };
};

C f()
{
    return C();
}

void g(const C &c)
{
}

int main()
{
    int i = 0;
    cin >> i;

    char cr = {i};

    int ii = 1024;
    char c2 = {ii};

    ii = -1;
    unsigned int ui = {ii};

    const auto & c = f();
    g(c);
    cout << "return 0" << endl;

    return 0;
}
