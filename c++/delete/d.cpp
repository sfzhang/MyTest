#include <iostream>

using namespace std;

void print(int a)
{
    cout << __func__ << endl;
}

void print(char a) = delete;

void print(double a) = delete;

struct C {

    ~C()
    {
        cout << "~C" << endl;
    }
};

C *c = nullptr;

struct S {
    ~S()
    {
        cout << "~S" << endl;
        delete c;
    }
} static g_s;

int main()
{
    print(1);
    /* error: use of deleted function
    print('1');
    print(1.);
    */

    return 0;
}
