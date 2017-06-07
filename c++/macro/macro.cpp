#include <cstdio>
#include <cstring>
#include <iostream>


#define DUMP_ERROR(func, stmt) \
    printf(#func "() %s\n", stmt);

#define VALUE(a, b) \
    ({ int c = a + b; c; })

using namespace std;

int main()
{
    DUMP_ERROR(add, "hello");

    cout << "value(1, 2) = " << VALUE(1, 2) << endl;
    cout << "value(100, -200) = " << VALUE(100, -200) << endl;
    cout << "value(-20, -30) = " << VALUE(-20, -30) << endl;

    return 0;
}
