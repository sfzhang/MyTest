#include <iostream>
#include <cfenv>
#include <cmath>

using namespace std;

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
    */
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

    return 0;
}
