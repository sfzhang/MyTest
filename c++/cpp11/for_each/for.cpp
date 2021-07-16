#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int *p = new int[n];
    int q[] = {1, 2, 3, 4};

    for (auto i: q) {
        cout << i << endl;
    }

    return 0;
}
