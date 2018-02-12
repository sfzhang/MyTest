#include <iostream>
#include <armadillo>
#include <fstream>
#include <cmath>

using namespace std;
using namespace arma;

int main()
{
    ifstream infile("./in.txt");

    double a = -M_PI;

    /* Rotate Y */
    mat t1 = { { cos(a),  0,       -sin(a), 0 },
               { 0,       1,       0,       0 },
               { sin(a),  0,       cos(a),  0 },
               { 0,       0,       0,       1 } };

    /* Rotate Z */
    double b = M_PI / 2;
    mat t2 = { { cos(b),  sin(b),  0,       0 },
               { -sin(b), cos(b),  0,       0 },
               { 0,       0,       1,       0 },
               { 0,       0,       0,       1 } };

    mat t = t2 * t1;

    double x, y, z;
    double vx, vy, vz;

    vec v = { 0, 0, 0, 1 };
    vec r = t * v;

    while (infile) {
        infile >> x >> y >> z >> vx >> vy >> vz;

        v = { x, y, z, 1 };
        vec m =  t * v;

        cout << m(0) << " " << m(1) << " " << m(2) << " ";

        v = { vx, vy, vz, 1 };
        m = t * v;

        double n = sqrt(pow((m(0) - r(0)), 2) + pow((m(1) - r(1)), 2) + pow((m(2) - r(2)), 2));
        cout << (m(0) - r(0)) / n << " " << (m(1) - r(1)) / n << " " << (m(2) - r(2)) / n << endl;
    }

    return 0;
}
