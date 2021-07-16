#include <iostream>
#include <cstring>
#include <type_traits>
#include <typeinfo>

template <typename T>
const T& max(T const &a, T const &b)
{
    return b < a ? a : b;
}

char const *max(char const *a, char const *b)
{
    return std::strcmp(a, b) < 0 ? a : b;
}

template <typename T>
T const &max(T const &a, T const &b, T const &c)
{
    return max(max(a, b), c);
}

const char * &f()
{
    static const char * a = "abc";
    return a;
}

int main()
{
    char const *s1 = "bc";
    char const *s2 = "ab";
    char const *s3 = "lu";

    // warning: returning reference to temporary [-Wreturn-local-addr]
//    auto m2 = ::max(s1, s2, s3);
    const auto &m2 = ::max(7, 42, 68);
    std::cout << typeid(m2).name() << std::endl;

    auto m3 = f();
    std::cout << typeid(m3).name() << std::endl;
    //cout << m2 << endl;
    return 0;
}
