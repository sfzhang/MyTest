#include <iostream>
#include <future>

using namespace std;

int main()
{
    future<int> f;
    {
        promise<int> p;
        f = p.get_future();
        p.set_value(1);
    }

    f.wait();
    cout << f.get() << endl;
    cout << f.get() << endl;

    cout << "end" << endl;
    return 0;
}
