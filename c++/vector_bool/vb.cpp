#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    vector<bool> vb(5);

    cout << "init:" << endl;

    for (size_t i = 0; i < vb.size(); i++) {
        cout << vb[i] << endl;
    }

    cout << "set true value:" << endl;

    for (size_t i = 0; i < vb.size(); i++) {
        vb[i] = true;
        cout << vb[i] << endl;
    }

    cout << "set false value:" << endl;

    for (size_t i = 0; i < vb.size(); i++) {
        vb[i] = false;
        cout << vb[i] << endl;
    }

    cout << "fill:" << endl;
    fill(vb.begin(), vb.end(), true);

    for (size_t i = 0; i < vb.size(); i++) {
        cout << vb[i] << endl;
    }


    return 0;
}
