#include <iostream>
#include <memory>

using namespace std;

class Test {

public:

    void print()
    {
        cout << "print" << endl;
        cout << a << endl;
    }

protected:

    int a;
};

struct C {
    int a;
};

std::shared_ptr<int> g_ptr(new int);

const std::shared_ptr<int> &getPtr()
{
    return g_ptr;
}

int main()
{
//    shared_ptr<Test> t;
//    t->print();
//
#if 0
    int b = 0;
    auto ptr_c = shared_ptr<C>(new C);
    auto ptr_a = shared_ptr<int>(ptr_c, &ptr_c->a);
    auto ptr_b = shared_ptr<int>(ptr_c, &b);

    cout << std::boolalpha
         << "ptr_c.owner_before(ptr_a): " << ptr_c.owner_before(ptr_a) << '\n'
         << "ptr_a.owner_before(ptr_c): " << ptr_a.owner_before(ptr_c) << '\n'
         << "ptr_c.owner_before(ptr_b): " << ptr_c.owner_before(ptr_b) << '\n'
         << "ptr_b.owner_before(ptr_c): " << ptr_b.owner_before(ptr_c) << '\n'
         << "ptr_b < ptr_a: " << (ptr_b < ptr_a) << '\n'
         << "ptr_a < ptr_b: " << (ptr_a < ptr_b) << '\n';
#endif

    *g_ptr = 1;

    const auto &ptr = getPtr();
    *ptr = 2;

    cout << *g_ptr << endl;

    return 0;
}
