#include <iostream>
#include <clocale>
#include <cwchar>

using namespace std;

int main()
{
    cout << cout.getloc().name() << endl;

    auto loc = setlocale(LC_ALL, "");

    cout << cout.getloc().name() << endl;

    ios::sync_with_stdio(false);
    //cout.imbue(locale(""));
    //wcout.imbue(locale(""));

    cout << "before set locale" << endl;
    cout << loc << endl;
    cout << "这是中文cout" << endl;
    fwide(stdout, 1);
    //cout << fwide(stdout, 1) << endl;
    //freopen(nullptr, "w", stdout);
    wcout << L"这是中文wcout" << endl;

    //loc = setlocale(LC_ALL, "");
    //fwide(stdout, 0);
    //freopen(nullptr, "w", stdout);
    fwide(stdout, 0);
    cout << "after set locale" << endl;
    cout << loc << endl;
    cout << "这是中文cout" << endl;
    wcout << L"这是中文wcout" << endl;

    return 0;
}
