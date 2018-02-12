/* final */
#include <iostream>
#include <string>

using namespace std;

class B {

public:

    virtual void print() const = 0;

};

class C: public B {

public:

    virtual string getName() const
    {
        return string("C");
    }

    virtual void print() const final
    {
        cout << getName() << endl;
    }

};

class D: public C {

public:

    virtual string getName() const
    {
        return string("D");
    }

    virtual void print() const
    {
        cout << "IN D: " << getName() << endl;
    }

};


int main()
{
    D d;
    d.print();
    return 0;
}
