#include <iostream>
#include <algorithm>

using namespace std;

int solution(int A[], int count)
{
    int min_depth = -1;

    /* find p */
    int i = 0;
    while (i < count) {
        int p = i;
        int q = -1;
        int r = -1;

        while (((i + 1) < count) && (A[i] > A[i+1])) {
            ++i;
        }

        cout << __LINE__ << " i: " << i << endl;
        if (i == p) {
            ++i;
            continue;
        }

        q = i;
        while (((i + 1) < count) && (A[i] < A[i+1])) {
            ++i;

            cout << __LINE__ << " i: " << i << endl;
            r = i;
            cout << p << " " << q << " " << r << endl;
            min_depth = max(min_depth, min(A[p] - A[q], A[r] - A[q]));
            cout << "min_depth: " << min_depth << endl;
        }

        if (i == q) {
            i++;
            continue;
        }

        cout << __LINE__ << " i: " << i << endl;
        r = i;
        cout << p << " " << q << " " << r << endl;
        min_depth = max(min_depth, min(A[p] - A[q], A[r] - A[q]));
    }

    return min_depth;
}

int main()
{
    int A[] = {0, 1, 3, -2, 0, 1, 0, -3, 2, 3};
    cout << solution(A, sizeof(A) / sizeof(A[0])) << endl;

    return 0;
}
