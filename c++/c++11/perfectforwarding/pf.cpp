/* Perfect forwarding */

#include <iostream>
#include <utility>

using namespace std;

void f(int &a)
{
    cout << "lvalue ref" << endl;
}

void f(int &&a)
{
    cout << "rvalue ref" << endl;
}

void f(const int &a)
{
    cout << "const lvalue ref" << endl;
}

void f(const int &&a)
{
    cout << "const rvalue ref" << endl;
}

template <typename T>
void perfect_forward(T &&t)
{
//    f(static_cast<T &&>(t));
    f(std::forward<T>(t));
}

int main()
{
    int a;
    int b;
    const int c = 1;
    const int d = 2;

    perfect_forward(a);
    perfect_forward(std::move(b));
    perfect_forward(c);
    perfect_forward(std::move(d));

    return 0;
}
