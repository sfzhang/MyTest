#include <boost/type_index.hpp>
#include <type_traits>
#include <iostream>

using namespace std;
using boost::typeindex::type_id_with_cvr;

template <typename T>
void f(T *param)
{
    cout << "        type(T): " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "        type(param): " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

template <typename T>
void g(T &&param)
{
    cout << "        type(T): " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "        type(param): " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

template <typename T>
void h(T param)
{
    cout << "        type(T): " << type_id_with_cvr<T>().pretty_name() << endl;
    cout << "        type(param): " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

int main()
{
    int x = 27;
    int &rx = x;
    int *px = &x;
    const int cx = x;
    const int *pcx = &cx;
    const int &rcx = cx;

    cout << "void f(T *param): " << endl;

    cout << "    f(&x): " << endl;
    f(&x);

    cout << "    f(px): " << endl;
    f(px);

    cout << "    f(&cx): " << endl;
    f(&cx);

    cout << "    f(pcx): " << endl;
    f(pcx);

    cout << "void g(T &&param): " << endl;

    cout << "    g(x): " << endl;
    g(x);

    cout << "    g(rx): " << endl;
    g(rx);

    cout << "    g(px): " << endl;
    g(px);

    cout << "    g(cx): " << endl;
    g(cx);

    cout << "    g(pcx): " << endl;
    g(pcx);

    cout << "    g(rcx): " << endl;
    g(rcx);

    cout << "    g(27): " << endl;
    g(27);

    cout << "    g(static_cast<const int&&>(27)): " << endl;
    g(static_cast<const int &&>(27));

    cout << "void h(T param): " << endl;
    const char * const cpcs = "abc";
    cout << "    h(cpcs): " << endl;
    h(cpcs);

    return 0;
}
