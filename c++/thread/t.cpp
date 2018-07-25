#include <iostream>
#include <thread>

using namespace std;

int main()
{
    cout << boolalpha
         << thread::hardware_concurrency() << endl;

    return 0;
}
