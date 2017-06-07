#include <iostream>
#include <memory>

using namespace std;

class Test {

public:

    void print()
    {
        cout << "print" << endl;
        cout << a << endl;
    }

protected:

    int a;
};

int main()
{
    shared_ptr<Test> t;
    t->print();
    return 0;
}
