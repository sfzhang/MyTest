#include <stdio.h>

struct no_array_0 {
    int a;
};

struct array_0 {
    int a;
    char d[0];
};

struct array_1 {
    int a;
    char d[1];
};

int main()
{
    printf("sizeof(no_array_0): %u; sizeof(array_0): %u; sizeof(array_1): %u\n",
           sizeof(struct no_array_0), sizeof(struct array_0),
           sizeof(struct array_1));
    return 0;
}
