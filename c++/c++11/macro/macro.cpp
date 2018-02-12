/* C99 macro */
#include <iostream>
#include <string>

using namespace std;

/* __func__ not defined in argument */
void print(string func = __func__)
{
    cout << func << endl;
}

void print(int a)
{
    cout << __func__ << ":" << a << endl;
}

int main(int arg, char *argv[])
{
    cout << "__STDC_HOSTED__: " << __STDC_HOSTED__ << endl;
    cout << "__STDC__: " << __STDC__ << endl;
//    cout << "__STDC_VERSION__: " << __STDC_VERSIOIN__ << endl;
    cout << "__STDC_ISO_10646__: " << __STDC_ISO_10646__ << endl;

    print();

    print(1);

    return 0;
}
