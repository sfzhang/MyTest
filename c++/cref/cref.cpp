#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <string>

using namespace std;

struct t {
    shared_ptr<int> a;
    string b;
    int c;
};

class CRef
{
public:

    ~CRef()
    {
        cout << "~CRef" << endl;
    }
};


CRef cref()
{
    return CRef();
}

int main()
{
    const auto &c_r = cref();

    cout << "begin" << endl;

    list<shared_ptr<int>> int_list;

    int_list.push_back(shared_ptr<int>(new int(1)));
    int_list.push_back(shared_ptr<int>(new int(2)));
    int_list.push_back(shared_ptr<int>(new int(3)));
    int_list.push_back(shared_ptr<int>(new int(4)));

    for (auto it = int_list.begin(); it != int_list.end(); ) {
        cout << it->use_count() << endl;
        it = int_list.erase(it);
    }

    t t1;
    t1.a = shared_ptr<int>(new int(5));
    t1.b = "hello";
    t1.c = 6;

    t t2 = t1;
    cout << *t2.a << " " << t2.b << " " << t2.c << endl;

    return 0;
}
