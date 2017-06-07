#include <cstddef>
#include <cstdio>
#include <cstring>
#include </home/fus/Git/hifu/utils/pub/hifutype.h>
#include </home/fus/Git/hifu/utils/pub/public.h>
#include </home/fus/Git/hifu/utils/pub/timehelper.h>
#include </home/fus/Git/hifu/utils/log/log.h>

using namespace std;

int main()
{
    printf("0.005 = %.2f\n", 0.005);
    printf("0.015 = %.2f\n", 0.015);
    printf("0.025 = %.2f\n", 0.025);
    printf("0.035 = %.2f\n", 0.035);

    printf("0.5 = %.0f\n", 0.5);
    printf("1.5 = %.0f\n", 1.5);
    printf("2.5 = %.0f\n", 2.5);
    printf("3.5 = %.0f\n", 3.5);

    std::size_t i = 100;
    printf("i[%u]\n", i);

    return 0;
}
