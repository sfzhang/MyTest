#include <iostream>

using namespace std;

template<typename T>
struct Type {
    enum { DEFINED = false };
};

template<>
struct Type<int> {
    enum { DEFINED = true };
};

int main()
{
    static_assert(Type<int>::DEFINED, "int type is not defined!");
    static_assert(Type<double>::DEFINED, "double type is not defined!");

    return 0;
}
