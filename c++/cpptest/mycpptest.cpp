#include <iostream>
#include <functional>

using namespace std;

class C {

public:

    void print()
    {
        cout << "C:print() is called!" << endl;
    }
};

int main(int argc, char *argv[])
{
    C c;

    auto f = std::bind(&C::print, &c);
    f();

    return 0;
}
