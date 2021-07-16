#include <iostream>

//static_assert(sizeof(long) == 4, "sizeof int must be 4");
static_assert(sizeof(int) == 4, "sizeof int must be 4");

template <typename T, typename U>
void bit_copy(T &a, U &b)
{
    static_assert(sizeof(T) == sizeof(U), "the parameters of bit_copy must have same width.");
}

int my_div(int a, int b)
{
    // error, expr must constexpr!
    // static_assert(b != 0, "b must not equal 0");
    return a / b;
}

int main()
{
    int a = 1;
    int b = 2;

    bit_copy(a, b);

    double c = 3;
    // compile failed!
    //bit_copy(a, c);

    return 0;
}
