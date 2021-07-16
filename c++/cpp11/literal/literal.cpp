#include <iostream>
#include <string>
#include <climits>

using namespace std;

struct Watt { Watt(int _w): w(_w) {} int w; };

Watt operator "" _w(unsigned long long l)
{
    cout << "ull" << endl;

    if (l > INT_MAX) {
        throw out_of_range{"out of range"};
    }

    return Watt(static_cast<int>(l));
}

Watt operator "" _w(const char *p, size_t l)
{
    cout << "str" << endl;
    string s(p, l);
    return operator ""  _w(stol(s));
}

void print(const Watt &w)
{
    cout << "Watt: " << w.w << endl;
}

int main()
{
    cout << "print(3_w): " << endl;
    print(3_w);

    cout << "print(\"103\"_w): " << endl;
    print("103"_w);

    try {
        cout << "print(111111111111111111111111111111111111_w): " << endl;
        print(111111111111111111111111111111111111_w);
    }
    catch (const exception &e) {
        cout << "catch exception: " << e.what() << endl;
    }

    try {
        cout << "print(\"999999999999999999999999999\"_w): " << endl;
        print("999999999999999999999999999"_w);
    }
    catch (const exception &e) {
        cout << "catch exception: " << e.what() << endl;
    }


    return 0;
}
