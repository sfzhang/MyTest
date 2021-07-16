#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void sort_and_print(int *a, int n)
{
    bubble_sort(a, n);

    cout << "------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a[] = {};
    sort_and_print(a, 0);

    int b[] = {1};
    sort_and_print(b, 1);

    int c[] = {1, 2};
    sort_and_print(c, 2);

    int d[] = {2, 1};
    sort_and_print(d, 2);
    
    int e[] = {1, 2, 3};
    sort_and_print(e, 3);

    int f[] = {1, 3, 2};
    sort_and_print(f, 3);

    int g[] = {2, 1, 3};
    sort_and_print(g, 3);

    int h[] = {2, 3, 1};
    sort_and_print(h, 3);

    int m[] = {3, 2, 1};
    sort_and_print(m, 3);

    int n[] = {5, 8, 5, 2, 9};
    sort_and_print(n, 5);

    return 0;
}
