#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

void test_auto()
{
    const auto a = 1;
    auto &b = a;
    // b is const int &
    // b = 3;

    const auto *p = &a;
    auto p2 = p;
    // p2 is const int &
    //*p2 = 2;

    char str[] = "abc";
    const char * const p_str = str;
    auto p_str_auto = p_str;
    // p_str_auto is const char *
    //p_str_auto[0] = 'q';
    p_str_auto = "def"; // OK

    auto i{1};
    // error: for deduction to ‘std::initializer_list’, use copy-list-initialization (i.e. add ‘=’ before the ‘{’)
    // auto d{1, 2, 3};

    cout << typeid(i).name() << endl;
}

template <typename T, typename U>
auto add(T t, U u)
{
    return t + u;
}

auto createIntList()
{
    auto p = {1, 2, 3};
    return p;
}

void func()
{
    vector<int> v;

    auto f = [&](const auto &new_v) { v = new_v; };

    // error:   template argument deduction/substitution failed:
    // f({1, 2, 3});
    auto p = {1, 2, 3};
    f(p);
}

int main()
{
    // error: inconsistent deduction for ‘auto’: ‘int’ and then ‘float’
    // auto i = 1, j = 3.14f;
    test_auto();

    add(1, 1.0);

    return 0;
}
