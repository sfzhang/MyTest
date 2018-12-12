#include <iostream>
#include <locale>

using namespace std;

int main()
{
    cout << "Startup" << endl;
    cout << cout.getloc().name() << endl;

    locale::global(locale(""));

    cout << "After set global locale" << endl;
    cout << cout.getloc().name() << endl;

    cout.imbue(locale());
    cout << "after Imube" << endl;
    cout << cout.getloc().name() << endl;

    return 0;
}
