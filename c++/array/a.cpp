#include <iostream>

using namespace std;

struct C {

    ~C() = default;
};

int main()
{
    C *p = new C[20]{};

    long *l = (long *)p;

    cout << *(l - 1) << endl;

    //delete (l - 1);
    //delete p;

    //delete [] p;
    //delete p;

    return 0;
}
