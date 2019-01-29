#include <iostream>
#include <cfenv>
#include <cmath>

using namespace std;

template <typename T>
T roundHalfUp(double d)
{
    return static_cast<T>(floor(d + 0.5));
}

int roundUp(double d)
{
    return static_cast<int>(floor(d + 0.5));
}

int roundDown(double d)
{
    return static_cast<int>(ceil(d - 0.5));
}


int main()
{
    /*
    if (0 == fesetround(FE_TOWARDZERO)) {
        cout << "nearbyint(2.3): " << nearbyint(2.3) << endl;
        cout << "nearbyint(3.8): " << nearbyint(3.8) << endl;
        cout << "nearbyint(2.5): " << nearbyint(2.5) << endl;
        cout << "nearbyint(-2.3): " << nearbyint(-2.3) << endl;
        cout << "nearbyint(-3.8): " << nearbyint(-3.8) << endl;
        cout << "nearbyint(-2.5): " << nearbyint(-2.5) << endl;
    }
    if (0 == fesetround(FE_TONEAREST)) {
        cout << "rint(2.3): " << rint(2.3) << endl;
        cout << "rint(3.8): " << rint(3.8) << endl;
        cout << "rint(2.5): " << rint(2.5) << endl;
        cout << "rint(-2.3): " << rint(-2.3) << endl;
        cout << "rint(-3.8): " << rint(-3.8) << endl;
        cout << "rint(-2.5): " << rint(-2.5) << endl;
    }

    struct A { int b; };
    const A *a;
    A *b = a;
    */

    cout << "Round up:" << endl;
    cout << "0: " << roundUp(0) << endl;
    cout << "0.1: " << roundUp(0.1) << endl;
    cout << "0.5: " << roundUp(0.5) << endl;
    cout << "0.9: " << roundUp(0.9) << endl;
    cout << "1.0: " << roundUp(1.0) << endl;
    cout << "1.2: " << roundUp(1.2) << endl;
    cout << "1.5: " << roundUp(1.5) << endl;
    cout << "1.8: " << roundUp(1.8) << endl;
    cout << "2.0: " << roundUp(2.0) << endl;
    cout << "2.4: " << roundUp(2.4) << endl;
    cout << "2.5: " << roundUp(2.5) << endl;
    cout << "2.8: " << roundUp(2.8) << endl;

    cout << "-0.1: " << roundUp(-0.1) << endl;
    cout << "-0.5: " << roundUp(-0.5) << endl;
    cout << "-0.9: " << roundUp(-0.9) << endl;
    cout << "-1.0: " << roundUp(-1.0) << endl;
    cout << "-1.2: " << roundUp(-1.2) << endl;
    cout << "-1.5: " << roundUp(-1.5) << endl;
    cout << "-1.8: " << roundUp(-1.8) << endl;
    cout << "-2.0: " << roundUp(-2.0) << endl;
    cout << "-2.4: " << roundUp(-2.4) << endl;
    cout << "-2.5: " << roundUp(-2.5) << endl;
    cout << "-2.8: " << roundUp(-2.8) << endl;

    cout << "Round down:" << endl;
    cout << "0: " << roundDown(0) << endl;
    cout << "0.1: " << roundDown(0.1) << endl;
    cout << "0.5: " << roundDown(0.5) << endl;
    cout << "0.9: " << roundDown(0.9) << endl;
    cout << "1.0: " << roundDown(1.0) << endl;
    cout << "1.2: " << roundDown(1.2) << endl;
    cout << "1.5: " << roundDown(1.5) << endl;
    cout << "1.8: " << roundDown(1.8) << endl;
    cout << "2.0: " << roundDown(2.0) << endl;
    cout << "2.4: " << roundDown(2.4) << endl;
    cout << "2.5: " << roundDown(2.5) << endl;
    cout << "2.8: " << roundDown(2.8) << endl;

    cout << "-0.1: " << roundDown(-0.1) << endl;
    cout << "-0.5: " << roundDown(-0.5) << endl;
    cout << "-0.9: " << roundDown(-0.9) << endl;
    cout << "-1.0: " << roundDown(-1.0) << endl;
    cout << "-1.2: " << roundDown(-1.2) << endl;
    cout << "-1.5: " << roundDown(-1.5) << endl;
    cout << "-1.8: " << roundDown(-1.8) << endl;
    cout << "-2.0: " << roundDown(-2.0) << endl;
    cout << "-2.4: " << roundDown(-2.4) << endl;
    cout << "-2.5: " << roundDown(-2.5) << endl;
    cout << "-2.8: " << roundDown(-2.8) << endl;

    cout << roundHalfUp<int>(1.5) << endl;
    cout << roundHalfUp<double>(1.5) << endl;

    return 0;
}
