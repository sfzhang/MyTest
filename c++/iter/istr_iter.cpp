#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    cout << "Please input string list: ";

    istream_iterator<double> eos;
    istream_iterator<double> iter(cin);

    ofstream ofs("1.txt");

    cout << "before while" << endl;
    while (iter != eos) {
        ofs << *iter << ' ' << *iter << ' ' << *iter << endl;
        iter++;
        /*
        cout << *iter << ' ' << *iter << ' ' << *iter << endl;
        cout << "before++" << endl;
        iter++;
        cout << "after++" << endl;
        */
    }

    ostream_iterator<string> oiter(cout, "|");

    oiter = "hello";
    oiter = "world";

    return 0;
}
