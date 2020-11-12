#include <cstdio>

using namespace std;

int main()
{
    alignas(double) unsigned char a[6];

    printf("sizeof: %d\n", sizeof(a));
    for (int i = 0; i < 6; i++) {
        printf("%x\n", (a + i));
    }

    return 0;
}
