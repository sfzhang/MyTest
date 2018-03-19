#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct S {
    int i;
    string str;

    S(int i_, const string &str_): i(i_), str(str_) {}
    S() { cout << "default constructo" << endl; }
    //S(const S&s){ cout << "copy constructor" << endl; }
    //S(S &&s) { cout << "move constructor" << endl; }

    ~S() {}
};

class P {
public:

    P(int *p): m_p(p) {}

    ~P() { delete m_p; }

protected:

    int *m_p;
};

int main()
{
    S s;
    S s3 = S();

    P p(new int{1});
    P p1 = p;

    return 0;
}

