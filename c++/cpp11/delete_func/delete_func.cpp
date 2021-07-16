#include <iostream>

using namespace std;

void f(int a)
{
    cout << a << endl;
}

void f(char c) = delete;

void f(double d) = delete;

struct S {

public:

    template<typename T>
    void f(T *)
    {
    }

};

template<> void S::f<void>(void *) = delete;

int main()
{
    f(1);

    // error: use of deleted function
    //f('c');

    float a = 1.0;
    // error: use of deleted function
    //f(a);

    S s;
    s.f(&a);

    void *p;
    // error: use of deleted function ‘void S::f(T*) [with T = void]’
    //s.f(p);

    return 0;
}
