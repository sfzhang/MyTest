#include <iostream>
#include "a.h"

E A::s_e = E::blue;

int main()
{
    A a(2.0);

    a.print();

    return 0;
}

