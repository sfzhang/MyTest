#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

void f1(atomic_int &i)
{
    while (i < 10) {
        if (i % 2) {
            cout << i + 1 << endl;
            i++;
        }
        this_thread::yield();
    }
}

void f2(atomic_int &i)
{
    while (i < 10) {
        if (!(i % 2)) {
            cout << i + 1 << endl;
            i++;
        }
        this_thread::yield();
    }
}

int main()
{
    atomic_int i(0);

    thread t1(f1, ref(i));
    thread t2(f2, ref(i));

    t1.join();
    t2.join();

    return 0;
}
