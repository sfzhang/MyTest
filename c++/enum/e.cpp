#include <iostream>
using namespace std;

template <int N>
enum Color {
    red = N,
    yellow,
};

int main()
{
    cout << Color<3>::red <<endl;
    return 0;
}
