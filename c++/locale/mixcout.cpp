#include <iostream>
#include <locale>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    locale::global(locale(""));

    cout.imbue(locale());
    wcout.imbue(locale());

    cout << __LINE__ <<  "cout中文" << endl;
    wcout << __LINE__ << L"wcout中文" << endl;

    cout << __LINE__ <<  "cout中文" << endl;
    wcout << __LINE__ << L"wcout中文" << endl;

    return 0;
}
