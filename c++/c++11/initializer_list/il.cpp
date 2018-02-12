/* initializer_list */

#include <iostream>
#include <vector>

using namespace std;

void test()
{
    char a = 9999;
    int b = 2.0f;

    /* error -Wnarrowing */
    //char c = { 9999 };
    //int d = { 2.0f };
}

class C {

public:

    C &operator[](initializer_list<int> l)
    {
        for (auto it = l.begin(); it != l.end(); it++) {
            m_idx.push_back(*it);
        }

        return *this;
    }

    C &operator=(int v)
    {
        if (!m_idx.empty()) {
            for (auto it = m_idx.begin(); it != m_idx.end(); it++) {
                m_data.resize((*it > m_data.size()) ? *it : m_data.size());
                m_data[*it - 1] = v;
            }
            m_idx.clear();
        }

        return *this;
    }

    void print()
    {
        for (const auto &v: m_data) {
            cout << v << " ";
        }
        cout << endl;
    }

    vector<int> m_idx;
    vector<int> m_data;
};

int main()
{
    test();

    C c;
    c[{2, 4, 6, 8}] = 1;
    c[{1, 3, 5, 7}] = 0;
    c.print();

    c[{1, 2, 3}] = 3;
    c.print();

    return 0;
}
