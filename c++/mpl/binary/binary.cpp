#include <iostream>

using namespace std;

template <unsigned long N>
struct binary {

    static const unsigned long value = 
        binary<N / 10>::value * 2 + N % 10;

};

template <>
struct binary<0> {

    static const unsigned long value = 0;

};

int main()
{
    cout << "101011100b: " << binary<101011100>::value << endl;

    return 0;
}
