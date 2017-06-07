#include <iostream>

using namespace std;

class Test {

public:

    void register()
    {
        cout << "register" << endl;
    }
};

int main()
{
    Test t;
    t.register();
    return 0;
}
