#include <iostream>
#include <string>
#include <locale>
#include <iomanip>

using namespace std;

int main()
{
    string s = "��";

    cout << "s: ";
    for (char c: s) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }
    cout << endl;

    string utf8_s = u8"��";
    cout << "u8: ";
    for (char c: utf8_s) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }
    cout << endl;

    return 0;
}
