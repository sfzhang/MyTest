#include <iostream>
#include <set>
#include <iomanip>

using namespace std;

class compare {

public:

    compare(int a = 100):
        m_a(a)
    {
    }

    bool operator()(int a, int b) const
    {
        cout << m_a << endl;
        return a < b;
    }

protected:

    int m_a;


protected:

    compare(const compare &other);

    compare& operator=(const compare &other);

};

int main()
{
    cout << setiosflags(ios::fixed) << setprecision(8) << 1 << endl;

    /*
    set<int, compare> s(compare(1));
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);

    for (const auto &v: s) {
        cout << v << endl;
    }
    */

    return 0;
}
