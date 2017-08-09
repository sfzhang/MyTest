#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    printf("0x123456: 0x%04x\n", htonl(0x123456));
    printf("0x000000: 0x%04x\n", htonl(0x000000));
    printf("0x000089: 0x%04x\n", htonl(0x000089));

    printf("68192238: 0x%d\n", htonl(68192238));
    printf("68192238: 0x%d\n", ntohl(68192238));

    return 0;
}
