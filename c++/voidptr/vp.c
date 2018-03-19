#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

typedef int (*add_t)(int, int);

int main()
{
    add_t a = add;
    printf("%d\n", a(1, 2));

    void *vp = a;

    return 0;
}
