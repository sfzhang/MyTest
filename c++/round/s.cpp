#include <iostream>

using namespace std;

int sub(double a, double b)
{
    return a - b;
}

double sub(double a, double b)
{
    return a - b;
}

template<typename T>
T add(double a, double b)
{
    return static_cast<T>(a + b);
}

int main()
{
    cout << add<int>(1.1, 1) << endl;
    cout << add<double>(1.1, 1) << endl;

    return 0;
}
