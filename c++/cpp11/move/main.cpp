#include <iostream>
#include <utility>

using namespace std;

class A {

public:

    A()
    {
        cout << "A()" << endl;
    }

    A(const A &)
    {
        cout << "A(const A &)" << endl;
    }

    A(A &&)
    {
        cout << "A(A &&)" << endl;
    }

    A &operator=(const A &)
    {
        cout << "operator=(const A&)" << endl;
        return *this;
    }

    A &operator=(A &&)
    {
        cout << "operator=(A &&)" << endl;
        return *this;
    }

};

class C {
public:

    A data() &
    {
        return a;
    }

    A data() &&
    {
        return std::move(a);
    }

private:

    A a;
};

int main()
{
    C c;
    auto a1 = c.data();

    auto a2 = C().data();

    C().data();

    return 0;
}
