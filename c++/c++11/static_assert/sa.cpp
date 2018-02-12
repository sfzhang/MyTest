/* static_assert */
#include <iostream>
#include <cstring>

using namespace std;

#define assert_static(e) \
    do { \
        enum { assert_static__ = 1 / (e) }; \
    } while (0)


template <typename T, typename U> 
void bit_copy(T& a, U& b)
{
//    assert_static(sizeof(a) == sizeof(b));
    static_assert(sizeof(a) == sizeof(b), "a diff b");
    memcpy(&a, &b, sizeof(b));
}

int main()
{
    int a = 1;
    double b;
    bit_copy(a, b);

    return 0;
}

