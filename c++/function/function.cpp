#include <functional>
#include <iostream>

using namespace std;

int main()
{
    function<bool(double, double)> func = less<double>();

    cout << func(1, 2) << endl;
    cout << func(2, 2) << endl;
    cout << func(2, 1) << endl;

    return 0;
}
