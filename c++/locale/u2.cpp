#include <iostream>
#include <locale>
#include <string>
#include <codecvt>

using namespace std;

int main()
{
    /*
    cout << locale().name() << endl;
    locale::global(locale("zh_CN.GBK"));
    cout << locale().name() << endl;
    */

    string raw = "บบ";

    cout << "raw: " << raw << endl;
    for (char c: raw) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }   
    cout << endl;

    string utf8 = u8"บบ";
    cout << "utf8: " << utf8 << endl;
    for (char c: utf8) {
        cout << hex << showbase << +(unsigned char)c << ' ';
    }   
    cout << endl;

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> ucs4conv;
    std::u32string u32s = ucs4conv.from_bytes(utf8);
    for (char32_t c: u32s) {
        cout << hex << showbase << +(char32_t)c << ' ';
    }   
    cout << endl;

    /*
    wstring ws = L"บบ";
    for (wchar_t c: utf8) {
        cout << hex << showbase << +(unsigned int)c << ' ';
    }   
    cout << endl;
    */

    return 0;
}
