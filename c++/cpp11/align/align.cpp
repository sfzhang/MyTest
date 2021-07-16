#include <cstdio>

using namespace std;

struct alignas(32) Color {
    double r;
    double g;
    double b;
    double a;
};

int main()
{
    int b;
    alignas(double) unsigned char a[6];

    printf("address of b: %x\n", &b);
    printf("sizeof: %d\n", sizeof(a));
    printf("alignof a: %d\n", alignof(a));
    for (int i = 0; i < 6; i++) {
        printf("%x\n", (a + i));
    }

    Color c;

    printf("%d, %x, %x, %x, %x, %x\n", alignof(Color), &c, &c.r, &c.g, &c.b, &c.a);

    return 0;
}
