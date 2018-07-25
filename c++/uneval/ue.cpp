#include <iostream>

using namespace std;

class C {

    C() = default;
    ~C() = delete;
};

int main()
{
    cout << sizeof(C) << endl;
}
