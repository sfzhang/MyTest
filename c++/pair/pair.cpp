#include <iostream>
#include <utility>

using namespace std;

int main()
{
    pair<int, int[10]> p;
    p.first = 1;
    cout << sizeof(p.second) << endl;
    return 0;
}
