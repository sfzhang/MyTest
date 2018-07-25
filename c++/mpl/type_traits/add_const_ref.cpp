#include <type_traits>
#include <iostream>

using namespace std;

template <typename T>
struct add_const_ref {
    typedef const T& type;
};

template <typename T>
struct add_const_ref<T &> {
    typedef T type;
};

int main()
{
    cout << boolalpha
         << is_same<add_const_ref<int>::type, const int &>::value << endl
         << is_same<add_const_ref<const int>::type, const int &>::value << endl
         << is_same<add_const_ref<int &>::type, int>::value << endl
         << is_same<add_const_ref<const int &>::type, const int>::value << endl;

    return 0;
}
