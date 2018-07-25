#include <cstdlib>
#include <climits>
#include <iostream>

using namespace std;

int main()
{
    //const char *p = "/home/fus/////../..//home/fus/Git//";
    const char *p = "///home///abc//";
    char rp[PATH_MAX + 1] = {0};
    if (realpath(p, rp)) {
        cout << rp << endl;
    }
    else {
        cout << "Invalid p: " << p << endl;
    }

    return 0;
}
