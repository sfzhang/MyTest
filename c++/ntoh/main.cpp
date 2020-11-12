#include <iostream>
#include <arpa/inet.h>

using namespace std;

int main()
{
    double d = -3.10842;

    uint32_t *d_p = (uint32_t*)(&d);
    cout << *d_p << "; " << htonl(*d_p) << endl;

    uint32_t i = 3490662720;

    cout << i << ": " << htonl(i) << "; " << ntohl(i) << endl;

    return 0;
}
