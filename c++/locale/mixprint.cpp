#include <iostream>
#include <locale>

using namespace std;

int main()
{
    printf("%d: %s\n", __LINE__, "print中文"); // narrow
    wprintf(L"%d: %ls\n", __LINE__, L"wprint中文"); // error

    locale::global(locale(""));

    printf("%d: %s\n", __LINE__, "print中文"); // narrow
    wprintf(L"%d: %ls\n", __LINE__, L"wprint中文"); // still no work until orientation changed

    freopen(nullptr, "w", stdout);

    wprintf(L"%d: %ls\n", __LINE__, L"wprint中文"); // OK
    printf("%d: %s\n", __LINE__, "print中文"); // error orientation

    return 0;
}
