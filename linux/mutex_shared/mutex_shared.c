#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
#ifdef _POSIX_THREAD_PROCESS_SHARED
    printf("define _POSIX_THREAD_PROCESS_SHARED\n");
#else
    printf("not define _POSIX_THREAD_PROCESS_SHARED\n");
#endif

    printf("sysconf() for _SC_THREAD_PROCESS_SHARED: %ld\n",
           sysconf(_SC_THREAD_PROCESS_SHARED));
    return 0;
}
