/* delegate constructor */

#include <iostream>

using namespace std;

struct B {

    B(int a)
    {
        cout << __func__ << endl;
        throw a;
    }

    B()
        try: B(1) {
            cout << __func__ << endl;
        }
        catch (...) {
            cout << "caught exception." << endl;
        }
};

int main()
{
    B b;
}
