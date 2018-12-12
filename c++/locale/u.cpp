#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main()
{
    string utf8 = u8"汉";

    cout << "UTF-8" << endl;
    for (char c: utf8) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }
    cout << endl;

    return 0;
}
