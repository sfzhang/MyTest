#include <iostream>
#include <utility>
#include <typeinfo>
#include <boost/type_index.hpp>

using namespace boost::typeindex;
using namespace std;

template <typename T>
void print(T &t)
{
    cout << "print(T &t)" << endl;
    cout << typeid(t).name() << endl;
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(t)>().pretty_name() << endl;
    cout << "-------------" << endl;
}

template <typename T>
void f(const T &&t)
{
    cout << "f(const T &&t)" << endl;
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(t)>().pretty_name() << endl;
    cout << "-------------" << endl;
}

template <typename T>
void g(T &&t)
{
    cout << "g(T &&t)" << endl;
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(t)>().pretty_name() << endl;
    cout << "-------------" << endl;
}

template <typename T>
void h(T t)
{
    cout << "h(T t)" << endl;
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(t)>().pretty_name() << endl;
    cout << "-------------" << endl;
}

void foo(int, double)
{
}

int main()
{
    /*
    int &&a = 0;
    cout << type_id_with_cvr<decltype(a)>().pretty_name() << endl;
    print(a);
    int &b = a;

    f(1);

    const int &x = 1;
    //f(x);

    //f(a);
    
    f(std::move(a));
    */

    cout << "g(0)" << endl;
    g(0);

    int x = 0;
    cout << "int x = 0; g(x)" << endl;
    g(x);

    int &a = x;
    cout << "int &a = x; g(a)" << endl;
    g(a);

    const int &b = x;
    cout << "int &a = x; g(a)" << endl;
    g(b);

    int &&r = 1;
    cout << "int &&r = 1; g(r)" << endl;
    g(r);

    cout << "g(std::move(r))" << endl;
    g(move(r));

    const char array[] = "abc";
    cout << "const char array[]; g(array)" << endl;
    g(array);

    cout << "const char array[]; print(array)" << endl;
    print(array);

    cout << "const char array[]; h(array)" << endl;
    h(array);

    const char * const ptr = "hello";
    cout << "const char * const" << endl;
    h(ptr);

    cout << "void foo(int, double)" << endl;
    g(foo);
    print(foo);
    h(foo);

    return 0;
}
