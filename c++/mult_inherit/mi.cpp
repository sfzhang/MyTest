#include <iostream>

using namespace std;

class Base {

public:

    virtual void print() = 0;

};

class Concrete1: public Base {

public:

    virtual void print()
    {
        cout << "C1" << endl;
    }
};

class Concrete2: public Base {

public:

    virtual void output()
    {
        print();
    }
};

class Impl: public Concrete1, public Concrete2 {
};

int main()
{
    Impl impl;
    impl.output();
    return 0;
}
