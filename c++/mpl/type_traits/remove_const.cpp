#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

int main()
{
    int b = 0;
    remove_const<const int *>::type a = &b;

    cout << typeid(a).name() << endl;

    cout << b << endl;
    //*a = 1;
    cout << b << endl;

    return 0;
}
