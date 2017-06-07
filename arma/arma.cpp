#include <iostream>
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

int main()
{
    vector<double> v = { 1, 2, 3, 4 };

    rowvec r(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        r(i) = v[i];
    }

    for (size_t i = 0; i < r.size(); i++) {
        cout << r[i] << endl;
    }

    return 0;
}
