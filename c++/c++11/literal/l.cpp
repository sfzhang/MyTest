/* literal */
#include <iostream>

using namespace std;

struct N {

    long double n;

};

ostream &operator<<(ostream &out, const N &n)
{
    return out << n.n << "(N)" << endl;
}

N operator "" _N(long double n)
{
    return N{n};
}

int main()
{
    cout << 123.45_N;
    return 0;
}
