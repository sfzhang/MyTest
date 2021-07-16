#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

atomic<bool> g_flag;

int thread_local g_i;

void f1()
{
    cout << &g_i << endl;
    int i = 0; 
    while (i < 50) {
        while (g_flag) {
            this_thread::yield();
        }

        cout << "t1: " << i << endl;
        i += 2;

        g_flag = true;
    }
}

void f2()
{
    cout << &g_i << endl;
    int i = 1; 
    while (i < 50) {
        while (!g_flag) {
            this_thread::yield();
        }

        cout << "t2: " << i << endl;
        i += 2;

        g_flag = false;
    }
}

int main()
{
    thread t1(f1);
    thread t2(f2);

    t1.join();
    t2.join();

    return 0;
}
