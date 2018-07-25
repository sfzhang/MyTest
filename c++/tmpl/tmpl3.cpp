#include <iostream>

using namespace std;

template <typename T>
struct B {
    T *elem;
};

template <typename T, int N>
struct C: B<T> {

    T *data()
    {
        return this->elem;
    }
};

int main()
{
    C<int, 5> c;
    c.data();

    return 0;
}

