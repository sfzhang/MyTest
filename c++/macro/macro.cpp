#include <cstdio>
#include <cstring>
#include <iostream>
#include <utility>
#include <string>
#include <vector>

#define DUMP_ERROR(func, stmt) \
    printf(#func "() %s\n", stmt);

#define VALUE(a, b) \
    ({ int c = a + b; c; })

#define THIS_IS_1 1
#define THIS_IS_2 2
#define THIS_IS_3 3
#define THIS_IS_4 4

enum Color {
    red,
    blue,
    green,
    yellow,
};

#define STR(a) #a

#define MAP_STR(a) { a, STR(a) }

using namespace std;

int main()
{
    DUMP_ERROR(add, "hello");

    cout << "value(1, 2) = " << VALUE(1, 2) << endl;
    cout << "value(100, -200) = " << VALUE(100, -200) << endl;
    cout << "value(-20, -30) = " << VALUE(-20, -30) << endl;

    cout << "--------------------------" << endl;

    vector<string> color_str = {
        STR(red), STR(blue), STR(green), STR(yellow) };

    for (const auto &s: color_str) {
        cout << s << endl;
    }

    return 0;
}
