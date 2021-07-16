#include <iostream>

using namespace std;

void no_except() noexcept
{
    throw int(1);
}

int main()
{
    cout << "before no_except()" << endl;

    no_except();

    cout << "after no_except()" << endl;

    return 0;
}
