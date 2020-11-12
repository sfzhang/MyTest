#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<string, int> m;

    m[""] = 1;

    cout << m.size() << endl;

    auto it = m.find("");
    if (it != m.end()) {
        cout << "found: " << it->second << endl;
    }
    else {
        cout << "NOT FOUND!" << endl;
    }

    return 0;
}
