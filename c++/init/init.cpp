#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;
int main()
{
    cout << sizeof(size_t) << endl;
    int32_t i = int32_t();
    cout << i << endl;

    char buff[200] = "";

    for (int i = 0; i < 200; ++i) {
        cout << int(buff[i]) << ":" << buff[i] << ' ';
    }
    
    return 0;
}
