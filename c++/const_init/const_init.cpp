#include <iostream>
#include "point2d.h"

typedef Point2d<int> Point2dInt;

int add(int a, int b)
{
    return a + b;
}

int a = 1;
int c = add(1, 2);

extern const Point2dInt c_2d;

using namespace std;

class SC {

public:

    SC()
    {
        cout << "SC()" << endl;
    }

    SC(int a)
    {
        cout << "SC(int)" << endl;
        m_a = a;
    }

    SC(const SC& sc):
        m_a(sc.m_a)
    {
        cout << "SC(const SC& sc)" << endl;
    }

    SC& operator=(const SC& sc)
    {
        cout << "operator=" << endl;
        if (this != &sc) {
            m_a = sc.m_a;
        }
        return *this;
    }

    int m_a;
};


extern const SC sc1;
const SC sc = sc1;
const SC sc1(5);

class Test {

public:

    static Test *instance()
    {
        return s_test;
    }

    Test()
    {
        m_2d = c_2d;
    }

    void print()
    {
        cout << m_2d.x() << " " << m_2d.y() << endl;
    }

protected:

    static Test *s_test;
    Point2dInt m_2d;
};

Test *Test::s_test = new Test();

const Point2dInt c_2d = Point2dInt(-1, -1);

int main()
{
    cout << c_2d.x() << " " << c_2d.y() << endl;
    Test::instance()->print();
    
    return 0;
}
