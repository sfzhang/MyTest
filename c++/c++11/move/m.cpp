/* move */
#include <iostream>
#include <utility>

using namespace std;

class M {

public:

    M(): m_d(new int(0)) {
        cout << "Construct: " << ++s_count << ", ptr: " << hex << m_d << endl;
    }

    M(const M& m): m_d(new int(*m.m_d)) {
        cout << "Copy construct: " << ++s_count << ", ptr: " << hex << m_d << endl;
    }

    M(M &&m): m_d(m.m_d) {
        m.m_d = nullptr;
        cout << "R copy construct: " << ++s_count << ", ptr: " << hex << m_d << endl;
    }

    M &operator=(const M &m)
    {
        cout << "operator=(const M &m)" << endl;
        if (this != &m) {
            delete m_d;
            m_d = new int(*m.m_d);
        }
        return *this;
    }

    M &operator=(M &&m)
    {
        cout << "operator=(M &&m)" << endl;
        if (this != &m) {
            delete m_d;
            m_d = m.m_d;
            m.m_d = nullptr;
        }

        return *this;
    }

    ~M() {
        cout << "Destructor: " << ++s_count << ", ptr: " << hex << m_d << endl;
    }

    int *m_d;
    static int s_count;
};

int M::s_count = 0;

M getM()
{
    M m;
    return m;
}

int main()
{
    M &&m = getM();

    cout << *m.m_d << endl;

    cout << "=====" << endl;

    M m2;
    *m2.m_d = 5;

    m = std::move(m2);

    cout << *m.m_d << endl;
    cout << *m2.m_d << endl;

    return 0;
}
