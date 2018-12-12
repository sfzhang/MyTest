#include <iostream>
#include <locale>
#include <string>
#include <cstring>

using namespace std;

class CustomCtype: public ctype<char> {

protected:

    virtual char_type do_toupper(char_type __c) const
    {
        cout << "call me" << endl;
        return __c + 1;
    }

};

int main()
{
    locale::global(locale(""));

    locale loc = locale().combine<ctype<char>>(locale(locale(), new CustomCtype));
    cout << loc.name() << endl;

    locale::global(loc);
    cout << locale().name() << endl;
    cout << toupper('a') << endl;

    cout.imbue(loc);
    cout << std::boolalpha << true << endl;
    cout << toupper('a') << endl;

    cout << std::boolalpha << "equal: " << (loc == locale()) << endl;

    cout << std::use_facet<std::ctype<char>>(loc).toupper('a') << endl;
    cout << std::use_facet<std::ctype<char>>(locale()).toupper('a') << endl;

    return 0;
}
