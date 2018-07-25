#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

template <typename T1, typename T2, typename T3>
struct replace_type {
    typedef T1 type;
};

template <typename T1, typename T3>
struct replace_type<T1, T1, T3> {
    typedef T3 type;
};

template <typename T1, typename T3>
struct replace_type<T1*, T1, T3> {
    typedef T3* type;
};

template <typename T1, typename T3>
struct replace_type<T1&, T1, T3> {
    typedef T3& type;
};

template <typename T1, size_t N, typename T3>
struct replace_type<T1[N], T1, T3> {
    typedef T3 type[N];
};

template <typename T1, size_t N, typename T3>
struct replace_type<T1*[N], T1, T3> {
    typedef T3* type[N];
};

template <typename T1, typename T2>
struct replace_type<T1(T1), T1, T2> {
    typedef T2 (*type)(T2);
};

int main()
{
    cout << boolalpha
         << typeid(replace_type<int, int, double>::type).name() << endl
         << typeid(replace_type<int, char, double>::type).name() << endl
         << typeid(replace_type<int*, int, double>::type).name() << endl
         << typeid(replace_type<const int*, const int, double>::type).name() << endl
         << typeid(replace_type<const int*, int, double>::type).name() << endl
         << typeid(replace_type<int const *[10], int const, double>::type).name() << endl
         << typeid(replace_type<int const [10], int const, float>::type).name() << endl
         << is_same<replace_type<int(*)(float), int, float>::type, float (*)(float)>::value << endl
         << typeid(replace_type<int&, int, double>::type).name() << endl;

    return 0;
}
