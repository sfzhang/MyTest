#include <iostream>
#include <clocale>
#include <string>
#include <cstring>

using namespace std;

class BoolName: public numpunct_byname<char> {

public:

    BoolName(const string &name):
        numpunct_byname<char>(name) {}

protected:

    virtual string do_truename() const {
        return "jiang";
    }

    virtual string do_falsename() const {
        return "gie";
    }
};

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
    locale loc(locale(""), new BoolName(""));
    cout << loc.name() << endl;

    cout << "global locale name: " << locale().name() << endl;

    cout << "imbue" << endl;
    locale::global(loc);
    cout << "global locale name: " << locale().name() << endl;

    cout.imbue(loc);
    cout << std::boolalpha << true << endl;

    cout << "------------------------" << endl;

    cout << toupper('a') << endl;

    locale loc2 (locale(""), new BoolName(""));

    locale::global(loc2);

    cout << toupper('a') << endl;

    locale loc3 = locale("").combine<ctype<char>>(locale(locale(""), new CustomCtype));
    cout << loc3.name() << endl;

    locale::global(loc3);
    cout << locale().name() << endl;
    cout << toupper('a') << endl;

    cout.imbue(loc3);
    cout << std::boolalpha << true << endl;
    cout << toupper('a') << endl;

    cout << std::boolalpha << "equal: " << (loc3 == locale("")) << endl;

    cout << std::use_facet<std::ctype<char>>(loc3).toupper('a') << endl;
    cout << std::use_facet<std::ctype<char>>(locale("")).toupper('a') << endl;

    return 0;
}
