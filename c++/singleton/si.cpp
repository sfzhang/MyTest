#include <iostream>
#include <tuple>
#include "a.h"
#include "b.h"

using namespace std;

int main()
{
    cout << "main" << endl;

    A::instance()->print();
}

