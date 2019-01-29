#include <iostream>
#include <type_traits>
#include <utility>
#include <boost/type_index.hpp>

using namespace std;
using namespace boost::typeindex;

void print(int &a, int &b)
{
    cout << "---- print ----" << endl;
    cout << (&a) << endl;
    cout << (&b) << endl;
    cout << is_same<decltype(a), decltype(b)>::value << endl;

    cout << "int &a: " << type_id_with_cvr<decltype(a)>().pretty_name() << endl;
    cout << a << endl;
}

void add(int &&a)
{
    a += 1;
}

int main()
{
    int a = 1;
    int &&b = std::move(a);
    int &c = b;

    cout << &b << endl;
    cout << &c << endl;
    cout << "int &&b: " << type_id_with_cvr<decltype(b)>().pretty_name() << endl;
    cout << "int &c: " << type_id_with_cvr<decltype(c)>().pretty_name() << endl;
    cout << is_same<decltype(b), decltype(c)>::value << endl;

    print(b, a);

    a = 2;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    cout << "add" << endl;
    add(std::move(a));
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
