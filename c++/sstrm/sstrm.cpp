#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    stringstream sstrm("-0");
    double a;
    sstrm >> a;
    cout << a << endl;
    return 0;
}
