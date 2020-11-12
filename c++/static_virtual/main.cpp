#include <iostream>

using namespace std;

struct B {

    static void sprint()
    {
        cout << "B" << endl;
    }

    virtual void vprint() const
    {
        sprint();
    }
};

struct C: public B {

    static void sprint()
    {
        cout << "C" << endl;
    }

    virtual void vprint() const
    {
        sprint();
    }
};

int main()
{
    B *b = new C;
    b->sprint();
    b->vprint();

    return 0;
}
