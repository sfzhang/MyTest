#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << numeric_limits<size_t>::max() << endl;
    cout << numeric_limits<size_t>::min() << endl;

    return 0;
}
