#include <iostream>
#include <typeinfo>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class RV {

public:

    RV(int a = 0): p(new int(a))
    {
        cout << "default construct" << endl;
    }
    //RV(int v = 0): p(new int(v)) {}

    ~RV()
    {
        delete p;
    }

    RV(const RV &rv):
        p(new int(*rv.p))
    {
        cout << "n copy" << endl;
    }

    RV(RV &&rv) noexcept: p(rv.p)
    {
        cout << "r copy " << endl;
        rv.p = nullptr;
    }

    RV& operator=(RV &rv)
    {
        cout << "operator=(RV &rv)" << endl;
        if (this != &rv) {
            delete p;
            p = new int(*rv.p);
        }
        return *this;
    }

    RV& operator=(RV &&rv) noexcept
    {
        cout << "operator=(RV &&rv)" << endl;
        if (this != &rv) {
            delete p;
            p = rv.p;
            rv.p = nullptr;
        }
        return *this;
    }

    int *p;
};

RV create(int a = 0)
{
    if (a > 0) {
        return RV(a);
    }
    else {
        return RV(-a);
    }
}

void print(RV rv)
{
    *rv.p = 3;
    cout << "print" << endl;
    cout << *rv.p << endl;
}

int main()
{
/*
    string a;
    cout << (&a)->size() << endl;
    cout << typeid(decltype(&a)).name() << endl;
    cout << typeid(decltype(a)).name() << endl;
    a = "helloworld";
    string &&ra = std::move(a);
    ra = "zsfasdfasdfasdfsad";
    cout << ra << endl;
    cout << a << endl;

    RV rv1;
    cout << *rv1.p << endl;

    RV &&rv2 = std::move(create());
    cout << *rv1.p << endl;
    cout << *rv2.p << endl;
    */

    RV rv = RV();

    //print(std::move(create()));
//    RV &&rv = create();
//
//    print(std::move(rv));

   // vector<RV> rv_list;
    //rv_list.push_back(RV());

    return 0;
}
