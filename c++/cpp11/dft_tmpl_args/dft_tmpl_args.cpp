#include <iostream>

using namespace std;

// error, class default template arguments must be from right to left
//template<typename T = int, typename U>
template<typename T, typename U=int>
struct C {
    T a;
    U b;
};

template<typename T = int, typename U>
void print(T a, U b)
{
    cout << a << "; " << b << endl;
}

int main()
{
    C<int, double> c;

    print(0.5, 4);

    return 0;
}
