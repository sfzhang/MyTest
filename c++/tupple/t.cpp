#include <tuple>
#include <utility>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    auto t = make_tuple(2.7, 299, "Hannibal");
    double c;
    string name;
    tie(c, ignore, name) = t;

    cout << c << ' ' << name << endl;

    return 0;
}
