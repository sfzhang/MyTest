#include <iostream>

using namespace std;

struct S {

    S() = default;

    ~S()
    {
        cout << "~S" << endl;
    }


    S(const S &) = default;

    /*
    S(const S &)
    {
        cout << "S(const S&)" << endl;
    }
    */

    /*
    S(S &&) = default;
    {
        cout << "S(S &&)" << endl;
    }
    */

    S& operator=(const S &) = delete;
    /*
    {
        cout << "operator=(const S &)" << endl;
        return *this;
    }
    */

    S& operator=(S &&) = default;
    /*
    {
        cout << "operator=(S &&)" << endl;
        return *this;
    }
    */

    void f()
    {
        cout << "f" << endl;
    }

};

S f()
{
    return S();
}

int main()
{
    S s1;
    S s2(s1);
    S s3(f()); // RVO
    s3 = f();

    S s4(std::move(f()));

    return 0;
}
