#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> vec{1, 2, 2, 3, 3, 3, 4, 5, 6, 2, 2 };

    for (const auto &v: vec) {
        cout << v << ' ';
    }
    cout << endl;

    auto p = unique(vec.begin(), vec.end());

    for ( ; p != vec.end(); p++) {
        cout << *p << ' ';
    }
    cout << endl;

    for (const auto &v: vec) {
        cout << v << ' ';
    }
    cout << endl;

    p = remove(vec.begin(), vec.end(), 2);

    for ( ; p != vec.end(); p++) {
        cout << *p << ' ';
    }
    cout << endl;

    for (const auto &v: vec) {
        cout << v << ' ';
    }
    cout << endl;

    return 0;
}
