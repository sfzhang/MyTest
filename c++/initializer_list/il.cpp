#include <iostream>
#include <string>

using namespace std;

class C {

public:

    C()
    {
        cout << "C()" << endl;
    }

    C(int i)
    {
        cout << "C(int i)" << endl;
    }

    C(double i)
    {
        cout << "C(double i)" << endl;
    }

    C(const string &i)
    {
        cout << "C(const string &i)" << endl;
    }

    C(initializer_list<int> il)
    {
        cout << "C(initializer_list<int> il)" << endl;
    }

};

int main()
{
    C();
    C{};

    C(1);
    C{1};

    C(1.1);

    /* error: narrowing conversion of ‘1.1000000000000001e+0’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
    C{1.1};
    */

    C("a");
    C{"a"};

    cout << "-----------" << endl;
    /* error: expected primary-expression before ‘)’ token
    C c1 = ();
    */
    C c2 = {};

    C c3 = (1);
    C c4 = {1};

    C c5 = (1.1);
    /* error: narrowing conversion of ‘1.1000000000000001e+0’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
    C c6 = {1.1};
    */

    C c7 = string("a");
    C c8 = {"a"};

    return 0;
}
