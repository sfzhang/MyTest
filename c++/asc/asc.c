#include <stdio.h>

char USM_Command_ASCII[10] = {0};

void LUE_ASCII_SPEED(int Value, int StartBit)
{
    int temp=10000;
    int ValueTemp=Value;
    int i=StartBit;
    //while(!(ValueTemp/temp))temp=temp/10;
    while(temp)
    {
        USM_Command_ASCII[i]=ValueTemp/temp+48;
        ValueTemp=ValueTemp%temp;
        temp=temp/10;
        i++;
    }
}

int main()
{
    LUE_ASCII_SPEED(23456, 3);

    for (int i = 0; i < 10; i++) {
        printf("%c\n", USM_Command_ASCII[i]);
    }

    return 0;
}
