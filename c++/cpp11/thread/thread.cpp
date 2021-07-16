#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;

void f1(mutex *m, condition_variable *cv, bool *flag)
{
    int i = 0; 
    while (i < 10) {
        unique_lock<mutex> lock(*m);
        cv->wait(lock, [flag]{ return *flag; });
        cout << "t1: " << i << endl;
        i++;

        *flag = false;
        cv->notify_all();
    }
}

void f2(mutex *m, condition_variable *cv, bool *flag)
{
    int i = 0; 
    while (i < 10) {
        unique_lock<mutex> lock(*m);
        cv->wait(lock, [flag]{ return !(*flag); });
        cout << "t2: " << i << endl;
        i++;

        *flag = true;
        cv->notify_all();
    }
}

int main()
{
    mutex m;
    condition_variable cv;
    bool flag{true};

    thread t1(f1, &m, &cv, &flag);
    thread t2(f2, &m, &cv, &flag);

    t1.join();
    t2.join();

    return 0;
}
