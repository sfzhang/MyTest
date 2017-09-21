#include <iostream>
#include <exception>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    cx_mat m(4, 4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m(i, j) = (datum::nan, datum::nan);
        }
    }

    try {
        /* Get the inverse of m, works */
        cx_mat m_i = inv(m);
        cout << "m_i:\n" << m_i << endl;

        cx_mat m1 = randu<cx_mat>(4, 4);

        /* Multiplication with m_i which is the inverse of m, WORKS too */
        cx_mat cx_m1 = m_i * m1;
        cout << "cx_m1:\n" << cx_m1 << endl;

        /* Multiplication with the inverse of m, CRASH! */
        cx_mat cx_m2 = inv(m) * m1;
        cout << "cx_m2:\n" << cx_m2 << endl;
    }
    catch (exception &e) {
        cout << "exception: " << e.what() << endl;
    }

    return 0;
}
