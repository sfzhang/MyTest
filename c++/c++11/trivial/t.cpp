/* trivial */
#include <iostream>

using namespace std;

struct NonTrivial2 {

    NonTrivial2();

    int w;
};

/* defaulted but not first declaration, still counts as user-provided!!!! */
NonTrivial2::NonTrivial2() = default;

struct Trivial2 {

    Trivial2() = default;
    Trivial2(int _w): w(_w) {}

    int w;
};

int main()
{
    cout << "is trivial: " << is_trivial<Trivial2>::value << endl;
    cout << "is pod: " << is_pod<Trivial2>::value << endl;
    cout << "is trivial: " << is_trivial<NonTrivial2>::value << endl;
    cout << "is pod: " << is_pod<NonTrivial2>::value << endl;
    return 0;
}
