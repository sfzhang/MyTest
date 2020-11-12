#include <memory>
#include <iostream>

using namespace std;

#define PR_DEBUG() \
    do { \
        cout << __func__ << ":" << __LINE__ << endl; \
    } while (0)


struct S2 {

    static shared_ptr<S2> instance()
    {
        PR_DEBUG();

        static shared_ptr<S2> s(new S2);
        return s;
    }

    void print();

    S2();

    ~S2();

    int *m_a;

};


struct S1 {

    static shared_ptr<S1> instance()
    {
        PR_DEBUG();

        static shared_ptr<S1> s(new S1);
        return s;
    }

    void print()
    {
        PR_DEBUG();
    }

    S1()
    {
        PR_DEBUG();
    }

    ~S1()
    {
        PR_DEBUG();
        S2::instance()->print();
    }
};

void S2::print()
{
    PR_DEBUG();
    cout << "m_a: " <<  *m_a << endl;
}

S2::S2():
    m_a(new int(1))
{
    PR_DEBUG();
    S1::instance()->print();
}

S2::~S2()
{
    delete m_a;
    m_a = nullptr;

    PR_DEBUG();
    S1::instance()->print();
}

int main()
{
    PR_DEBUG();
    S2::instance()->print();
    return 0;
}
