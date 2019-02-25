#include <iostream>
#include <vector>
#include <functional>

using namespace std;

using FilterContainer = vector<function<void()>>;

void filter(FilterContainer &c)
{
    static int i = 0;
    c.push_back([]{ cout << i << endl; });
    i++;
}

int main()
{
    FilterContainer c;

    filter(c);
    filter(c);
    filter(c);

    for (const auto &f: c) {
        f();
    }

    return 0;
}
