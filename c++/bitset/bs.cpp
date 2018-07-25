#include <bitset>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    bitset<sizeof(int)> b = 10;

    cout << b << endl;
    cout << b.to_string({'a'}, {'b'}) << endl;

    return 0;
}
