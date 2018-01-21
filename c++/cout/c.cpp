#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int a = 0;

    while (1) {

        cin >> a;

        if (cin.good()) {
            cout << "OK: " << a << endl;
        }
        else {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
