#include <iostream>
#include <string>
#include <locale>
#include <iomanip>

using namespace std;

int main()
{
    string s = "汉";

    cout << "s: ";
    for (char c: s) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }
    cout << endl;

    string utf8_s = u8"汉";
    cout << "u8: ";
    for (char c: utf8_s) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }
    cout << endl;

    u16string utf16_s = u"汉";
    cout << "u16: ";
    for (char16_t c: utf16_s) {
        cout << hex << showbase << c << '(';

        auto uc = (unsigned char *)&c;
        cout << hex << showbase << +*uc << ' ' << +*(uc+1) << ')' << endl;
    }

    u32string utf32_s = U"汉";
    cout << "u32: ";
    for (char32_t c: utf32_s) {
        cout << hex << showbase << c << '(';

        auto uc = (unsigned char *)&c;
        cout << hex << showbase << +*uc << ' ' << +*(uc+1) << ' ' << +*(uc+2) << ' ' << +*(uc+3) << ')' << endl;
    }

    wstring ws = L"汉";
    cout << "ws: ";
    for (wchar_t c: ws) {
        cout << showbase << hex << c << '(';

        cout << sizeof(c) << endl;
        auto uc = (unsigned char *)&c;
        cout << hex << showbase << +*uc << ' ' << +*(uc+1) << ' ' << +*(uc+2) << ' ' << +*(uc+3) << ')' << endl;
    }

    return 0;
}
