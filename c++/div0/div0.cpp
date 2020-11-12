#include <iostream>
#include <limits>
using namespace std;

int main()
{
    double d = 1.5 - 1.5;

    cout << 1.0 / 0 << endl;

    if (0 == d) {
        cout << "0 == d" << endl;
    }

    double a, b, c = 1;
    cout << a << endl << b << endl << c << endl;

    double min = numeric_limits<double>::lowest();
    double max = numeric_limits<double>::max();

    cout << max - min << endl;

    return 0;
}
