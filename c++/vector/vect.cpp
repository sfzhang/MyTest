#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> vv;
    vv.push_back(1);
    vv.push_back(2);
    vv.push_back(3);
    vv.push_back(4);

    for (auto it = vv.begin(); it != vv.end(); ) {
        it = vv.erase(it);
    }

    vector<vector<int>> v(3);

    cout << v.size() << endl;

    vector<bool> vb;
    vb.assign(5, false);
    cout << vb.size() << endl;
    for (const auto &b: vb) {
        cout << b << " ";
    }
    cout << endl;

    vb.assign(10, true);
    cout << vb.size() << endl;
    for (const auto &b: vb) {
        cout << b << " ";
    }
    cout << endl;

    vb.assign(4, false);
    cout << vb.size() << endl;
    for (const auto &b: vb) {
        cout << b << " ";
    }
    cout << endl;

    vb.assign(4, true);
    cout << vb.size() << endl;
    for (const auto &b: vb) {
        cout << b << " ";
    }
    cout << endl;

    return 0;
}
