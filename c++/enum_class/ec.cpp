#include <iostream>

enum class E_C {
    a,
    b,
    c
};

using namespace std;

#define DCMDATA_ANSI_ESCAPE_CODE_LINE       "\033[1m\033[30m"

int main()
{
    E_C c = E_C(1);
    cout << 1 << DCMDATA_ANSI_ESCAPE_CODE_LINE << 2 << endl;
    cout << int(c) << endl;
    return 0;
}

