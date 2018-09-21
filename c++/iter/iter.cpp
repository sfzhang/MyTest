#include <vector>
#include <typeinfo>
#include <iostream>
#include <string>

using namespace std;

struct trivial {
};

struct not_trivial {
    string s;
};

int main()
{
    cout << typeid(vector<double>::iterator::difference_type).name() << endl;

    vector<double>::iterator::difference_type a;
    cout << typeid(a).name() << endl;

    if (typeid(a) == typeid(ptrdiff_t)) {
        cout << "equal" << endl;
    }

    cout << sizeof(vector<int>::iterator::difference_type) << endl;

    cout << __is_trivial(trivial) << endl;
    cout << is_trivial<trivial>::value_type() << endl;
    cout << __is_trivial(not_trivial) << endl;

    return 0;
}
