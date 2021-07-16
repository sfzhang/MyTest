#include <iostream>

using namespace std;

int main()
{
#ifdef __STDC_HOSTED__
    cout << "__STDC_HOSTED__: " << __STDC_HOSTED__ << endl;
#else
    cout << "__STDC_HOSTED__ NOT defined!" << endl;
#endif

#ifdef __STDC__
    cout << "__STDC__: " << __STDC__ << endl;
#else
    cout << "__STDC__ NOT defined!" << endl;
#endif

#ifdef __STDC_VERSION
    cout << "__STDC_VERSION__: " << __STDC_VERSION__ << endl;
#else
    cout << "__STDC_VERSION__ NOT defined!"  << endl;
#endif

#ifdef __STDC_ISO_10646__
    cout << "__STDC_ISO_10646__: " << __STDC_ISO_10646__ << endl;
#else
    cout << "__STDC_ISO_10646__ NOT defined!" << endl;
#endif

    return 0;
}
