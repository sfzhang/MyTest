#include <functional>
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;
using namespace std::placeholders;

enum E {
    e1,
    e2,
};

struct C {

    void f(int i)
    {
        cout << __func__ << ": " << i << endl;
    }

    void g(double d)
    {
        cout << __func__ << ": " << d << endl;
    }

    void h(E e)
    {
        cout << __func__ << ": " << static_cast<int>(e) << endl;
    }

};

template <typename C>
struct IInvoker {

    virtual void invoke(C *c, const string &param) = 0;

};

template <typename C, typename T>
struct Invoke: public IInvoker<C> {

    using F = void (C::*)(T);

    Invoke(F func): m_func(func) {};

    template <typename U = T>
    typename std::enable_if<std::is_same<T, int>::value, U>::type covert(const string &param)
    {
        return stoi(param);
    }

    template <typename U = T>
    typename std::enable_if<std::is_same<T, double>::value, U>::type covert(const string &param)
    {
        return stod(param);
    }

    template <typename U = T>
    typename std::enable_if<std::is_same<T, string>::value, U>::type covert(const string &param)
    {
        return param;
    }

    virtual void invoke(C *obj, const string &param) override
    {
        (obj->*m_func)(covert(param));
    }

    F m_func;

};

int main()
{
    cout << boolalpha
         << std::is_same<int, E>::value << endl;
    C c;

    Invoke<C, int> i1(&C::f);
    i1.invoke(&c, "123");

    /*
    Invoke<C, double> i2(&C::g);
    i2.invoke(&c, "0.5");
    */

    return 0;
}
