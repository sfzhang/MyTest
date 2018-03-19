#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(vector<int> &v)
{
    ssize_t i = 0;
    ssize_t j = 0;
    int tmp = 0;
    for (i = 1; i < static_cast<ssize_t>(v.size()); i++) {
        tmp = v[i];
        for (j = i - 1; (j >= 0) && (v[j] > tmp); j--) {
            v[j + 1] = v[j];
        }
        v[j + 1] = tmp;
    }
}

void selection_sort(vector<int> &v)
{
    int i, j, k, tmp;

    for (i = 0; i < static_cast<int>(v.size()); i++) {
        k = i;
        for (j = i + 1; j < static_cast<int>(v.size()); j++) {
            if (v[k] > v[j]) {
                k = j;
            }
        }

        if (k != i) {
            tmp = v[k];
            v[k] = v[i];
            v[i] = tmp;
        }
    }
}

void bubble_sort(vector<int> &v)
{
    int i, j, last_swap, tmp;
    bool over = false;

    for (i = v.size() - 1; i > 0; i = last_swap) {
        last_swap = i - 1;
        over = true;

        for (j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
                last_swap = j;
                over = false;
            }
        }

        if (over) {
            cout << i << ":" << j << " over" << endl;
            break;
        }
    }
}

int mpartition(vector<int> &v, int l, int r)
{
    int base = v[l];
    while (l < r) {
        while ((l < r) && (base <= v[r])) r--;
        if (l < r) {
            v[l++] = v[r];
        }

        while ((l < r) && (base > v[l])) l++;
        if (l < r) {
            a[r--] = a[l];
        }
    }

    a[l] = base;
    return l;
}

int main()
{
    vector<int> v{3, 4, 1, 5, 9, 4, 7, 6, 8, 0, 2};

    //vector<int> v{1, 2, 3, 4, 6, 8 };

    //insertion_sort(v);
    //selection_sort(v);
    bubble_sort(v);


    for (const auto &a: v) {
        cout << a << " ";
    }

    cout << endl;
    return 0;
}
