#include <vector>
#include <iostream>
#include <cstdint>

using namespace std;

int bsearch(const vector<int> &nums, int left, int right, int n)
{
    while (right >= left) {
        size_t mid = (left + right) / 2;
        if (nums[mid] == n) {
            return mid;
        }
        else if (nums[mid] > n) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return left;
}

int main()
{
    int a = 2147483648 * 10;

    cout << "{0}, 0: " << bsearch({0}, 0, 0, 0) << endl;
    cout << "{0}, 1: " << bsearch({0}, 0, 0, 1) << endl;
    cout << "{0}, -1: " << bsearch({0}, 0, 0, -1) << endl;

    cout << "{1, 5}, -1: " << bsearch({1, 5}, 0, 1, -1) << endl;
    cout << "{1, 5}, 1: " << bsearch({1, 5}, 0, 1, 1) << endl;
    cout << "{1, 5}, 2: " << bsearch({1, 5}, 0, 1, 2) << endl;
    cout << "{1, 5}, 5: " << bsearch({1, 5}, 0, 1, 5) << endl;
    cout << "{1, 5}, 6: " << bsearch({1, 5}, 0, 1, 6) << endl;

    cout << "{1, 3, 6, 7, 10}, 0: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 0) << endl;
    cout << "{1, 3, 6, 7, 10}, 1: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 1) << endl;
    cout << "{1, 3, 6, 7, 10}, 2: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 2) << endl;
    cout << "{1, 3, 6, 7, 10}, 3: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 3) << endl;
    cout << "{1, 3, 6, 7, 10}, 4: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 4) << endl;
    cout << "{1, 3, 6, 7, 10}, 6: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 6) << endl;
    cout << "{1, 3, 6, 7, 10}, 7: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 7) << endl;
    cout << "{1, 3, 6, 7, 10}, 8: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 8) << endl;
    cout << "{1, 3, 6, 7, 10}, 10: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 10) << endl;
    cout << "{1, 3, 6, 7, 10}, 11: " << bsearch({1, 3, 6, 7, 10}, 0, 4, 11) << endl;

    return 0;
}
