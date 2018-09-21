#include <iostream>
using namespace std;

class Solution {
public:

    int solution(int A[]) {
        int count = 1;
        int i = 0;
        while (A[i] != -1) {
            count++;
            i = A[i];
        }
        return count;
    }
};

int main()
{
    Solution s;
    int A[] = {1, 4, -1, 3, 2};
    cout << s.solution(A) << endl;

    int B[] = {1, 2, 3, 4, 5, 6, 7, -1};
    cout << s.solution(B) << endl;

    return 0;
}
