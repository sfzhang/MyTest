#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s = "herewego";
    make_heap(s.begin(), s.end());

    cout << s << endl;

    return 0;
}
