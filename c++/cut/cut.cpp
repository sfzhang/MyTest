#include <iostream>
#include <list>
#include <cassert>

using namespace std;

void cut(std::list<double> &slice, double head, double tail)
{
    size_t head_idx = 0;
    auto head_iter = slice.begin();
    while ((head_iter != slice.end()) && (*head_iter < head)) {
        head_iter++;
        head_idx++;
    }

    if (head_iter == slice.end()) {
        return;
    }

    size_t tail_idx = 0;
    auto tail_iter = slice.begin();
    while ((tail_iter != slice.end()) && (*tail_iter <= tail)) {
        tail_iter++;
        tail_idx++;
    }

    if (tail_iter == slice.begin()) {
        return;
    }

    /* merge */
    if (0 == (head_idx % 2)) {
        auto iter = slice.erase(head_iter, tail_iter);
        if (1 == (tail_idx % 2)) {
            slice.insert(iter, tail);
        }
    }
    else {
        auto iter = slice.erase(head_iter, tail_iter);
        if (1 == (tail_idx % 2)) {
            iter = slice.insert(iter, tail);
        }
        slice.insert(iter, head);
    }
}

void dump(const std::list<double> &slice)
{
    for (const auto &v: slice) {
        cout << v << " ";
    }

    cout << endl;
}

int main()
{
    list<double> slice{0, 10};

    cut(slice, -1, -0.1);
    dump(slice);
    assert(slice == list<double>({0, 10}));

    cut(slice, 10.1, 100);
    dump(slice);
    assert(slice == list<double>({0, 10}));

    cut(slice, -10, 5);
    dump(slice);
    assert(slice == list<double>({5, 10}));

    cut(slice, 7, 12);
    dump(slice);
    assert(slice == list<double>({5, 7}));

    cut(slice, 5.5, 6.5);
    dump(slice);
    assert(slice == list<double>({5, 5.5, 6.5, 7}));

    cut(slice, 5.15, 5.35);
    dump(slice);
    assert(slice == list<double>({5, 5.15, 5.35, 5.5, 6.5, 7}));

    cut(slice, 6.75, 6.9);
    dump(slice);
    assert(slice == list<double>({5, 5.15, 5.35, 5.5, 6.5, 6.75, 6.9, 7}));

    cut(slice, 5.1, 5.2);
    dump(slice);
    assert(slice == list<double>({5, 5.1, 5.35, 5.5, 6.5, 6.75, 6.9, 7}));

    cut(slice, 5.2, 5.4);
    dump(slice);
    assert(slice == list<double>({5, 5.1, 5.4, 5.5, 6.5, 6.75, 6.9, 7}));

    cut(slice, 5.05, 6.6);
    dump(slice);
    assert(slice == list<double>({5, 5.05, 6.6, 6.75, 6.9, 7}));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 10);
    dump(slice);
    assert(slice == list<double>({}));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 6.5);
    dump(slice);
    assert(slice == list<double>({ 6.5, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 5.5);
    dump(slice);
    assert(slice == list<double>({ 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0.5, 10);
    dump(slice);
    assert(slice == list<double>({ 0, 0.5 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 10);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2.5, 10);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 2.5 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2.5, 4.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 2.5, 4.5, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2.5, 7.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 2.5, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2.5, 3.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 2.5, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2.5, 2.9);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 2.5, 2.9, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 3.9);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 4.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4.5, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 5.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 6.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 6.5, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 7.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3.5, 9.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, -0.5);
    assert(slice == list<double>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 1);
    dump(slice);
    assert(slice == list<double>({ 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 3);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 2);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1.5, 5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 8);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 0);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 1);
    dump(slice);
    assert(slice == list<double>({ 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 2);
    dump(slice);
    assert(slice == list<double>({ 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 3);
    dump(slice);
    assert(slice == list<double>({ 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 4);
    dump(slice);
    assert(slice == list<double>({ 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 7);
    dump(slice);
    assert(slice == list<double>({ 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 8);
    dump(slice);
    assert(slice == list<double>({ 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, -1, 9);
    dump(slice);
    assert(slice == list<double>({ }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 1);
    dump(slice);
    assert(slice == list<double>({ 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 2);
    dump(slice);
    assert(slice == list<double>({ 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 3);
    dump(slice);
    assert(slice == list<double>({ 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 4);
    dump(slice);
    assert(slice == list<double>({ 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 7);
    dump(slice);
    assert(slice == list<double>({ 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 8);
    dump(slice);
    assert(slice == list<double>({ 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 9);
    dump(slice);
    assert(slice == list<double>({ }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 0, 10);
    dump(slice);
    assert(slice == list<double>({ }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 1);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2.5, 2.5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 2.5, 2.5, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 2);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 3);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 4);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 7);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 8);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 1, 10);
    dump(slice);
    assert(slice == list<double>({ 0, 1 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 2);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 3);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 4);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 6);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 7);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 8);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 2, 90);
    dump(slice);
    assert(slice == list<double>({ 0, 1 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 3);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 4);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 5);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 6);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 7);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 8);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 3, 90);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 7, 7);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 7, 8);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 7, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 7, 90);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 8, 8);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 8, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 8, 90);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 9, 9);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    slice = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cut(slice, 9, 90);
    dump(slice);
    assert(slice == list<double>({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

    return 0;
}
