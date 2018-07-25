#include "timehelper.h"
#include "point3d.h"
#include <iostream>

using namespace std;

using Point3dDouble = Point3d<double>;

int main()
{
    Point3dDouble p0(1, 2, 3);
    Point3dDouble v0(2, 3, -1);

    TIME_INIT;

    TIME_BEGIN;

    int n = 8000000;
    for (int i = 0; i < n; ++i) {
        Point3dDouble p1(i, 2 * i, -i - 1);
        auto v = p0 - p1;
//        cout << v.dot(v0) << endl;
    }

    TIME_END;
    TIME_SPEND(n);

    return 0;
}
