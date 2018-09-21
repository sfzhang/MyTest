#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct st {
    size_t i;
    size_t b;
};

class C {

public:

    C(int i): m_i(i) {}

    int &get()
    {
        return m_i;
    }

    const int& get() const
    {
        return m_i;
    }

protected:

    int m_i;
};

int main()
{

    ssize_t sd = -100000000000;
    printf("%d\n", sd);
    printf("%ld\n", sd);
    printf("%zd\n", sd);

    double value = 25;
    stringstream sstrm;
    sstrm << fixed << setprecision(0) << value;
    cout << sstrm.str() << endl;

    C c(10);

    c.get() = 5;
    cout << c.get() << endl;

    vector<st> st_list;
    st_list.push_back(st{10, 0});
    cout << st_list[0].i << " " << st_list[0].b << endl;

    sstrm.str("");
    sstrm.clear();
    string slice_location = "8.01999999999999";

    sstrm << slice_location;
    value = 0;
    sstrm >> value;
    cout << value << endl;

    sstrm.clear();
    sstrm.str("");
    sstrm.setf(ios::fixed);
    sstrm << setprecision(2) << value;

    slice_location = sstrm.str();

    cout << slice_location << endl;;

    sstrm.clear();
    sstrm.str("");
    sstrm.fill('0');
    sstrm.width(6);

    sstrm << 6;

    cout << sstrm.str() << endl;

    sstrm.str(string());

    sstrm << fixed << setprecision(2) << 1.555;
    double v;
    sstrm >> v;
    cout << sstrm.str() << endl;
    cout << v << endl;
    return 0;
}
